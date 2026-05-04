
#include "SensorAnalysisService.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/PrivateUser.h"
#include <cmath>
#include <chrono>
#include <algorithm>
#include <numeric>
using namespace std;

static const double PI_SA = 3.14159265358979323846;

SensorAnalysisService::SensorAnalysisService ( SensorDAO& sensorDAO,
                                                MeasurementDAO& measurementDAO,
                                                UserDAO& userDAO )
    : sensorDAO(sensorDAO),
      measurementDAO(measurementDAO),
      userDAO(userDAO) {}

double SensorAnalysisService::haversineKm ( double lat1, double lon1,
                                             double lat2, double lon2 )
{
    const double R = 6371.0;
    double dLat = ( lat2 - lat1 ) * PI_SA / 180.0;
    double dLon = ( lon2 - lon1 ) * PI_SA / 180.0;
    double a = sin( dLat / 2 ) * sin( dLat / 2 )
             + cos( lat1 * PI_SA / 180.0 ) * cos( lat2 * PI_SA / 180.0 )
             * sin( dLon / 2 ) * sin( dLon / 2 );
    return R * 2.0 * atan2( sqrt( a ), sqrt( 1.0 - a ) );
}

map<string, double> SensorAnalysisService::computeAvgVector ( const string& sensorId,
                                                               const string& from,
                                                               const string& to )
{
    vector<Measurement> meas = measurementDAO.getBySensor( sensorId, from, to );

    map<string, vector<double>> valsByAttr;
    for ( const Measurement& m : meas )
    {
        if ( m.getIsValid() )
            valsByAttr[ m.getAttributeId() ].push_back( m.getValue() );
    }

    map<string, double> avgVector;
    for ( auto& kv : valsByAttr )
    {
        double sum = accumulate( kv.second.begin(), kv.second.end(), 0.0 );
        avgVector[ kv.first ] = sum / kv.second.size();
    }
    return avgVector;
}

double SensorAnalysisService::euclideanDistance ( const map<string, double>& v1,
                                                   const map<string, double>& v2 )
{
    const vector<string> attrs = { "O3", "SO2", "NO2", "PM10" };
    double sum = 0.0;
    for ( const string& a : attrs )
    {
        auto it1 = v1.find( a );
        auto it2 = v2.find( a );
        if ( it1 == v1.end() || it2 == v2.end() ) continue;
        double diff = it1->second - it2->second;
        sum += diff * diff;
    }
    return sqrt( sum );
}

double SensorAnalysisService::stdDev ( const vector<double>& values )
{
    if ( values.size() < 2 ) return 0.0;
    double mean = accumulate( values.begin(), values.end(), 0.0 ) / values.size();
    double sq_sum = 0.0;
    for ( double v : values ) sq_sum += ( v - mean ) * ( v - mean );
    return sqrt( sq_sum / values.size() );
}

vector<SensorScore> SensorAnalysisService::rankBySimilarity ( const string& refSensorId,
                                                               const string& from,
                                                               const string& to )
{
    auto t_start = chrono::high_resolution_clock::now();

    map<string, double> refVec = computeAvgVector( refSensorId, from, to );
    vector<SensorScore> result;
    if ( refVec.empty() ) return result;

    vector<Sensor> sensors = sensorDAO.getAllSensors();
    for ( const Sensor& s : sensors )
    {
        if ( s.getSensorId() == refSensorId || !s.getIsReliable() ) continue;

        map<string, double> vec = computeAvgVector( s.getSensorId(), from, to );
        if ( vec.empty() ) continue;

        result.push_back( { s.getSensorId(), euclideanDistance( refVec, vec ) } );
    }

    sort( result.begin(), result.end(),
          []( const SensorScore& a, const SensorScore& b )
          { return a.score < b.score; } );

    return result;
}

ReliabilityReport SensorAnalysisService::analyzeReliability ( const string& sensorId )
{
    auto t_start = chrono::high_resolution_clock::now();
    const double THRESHOLD   = 2.0;
    const int    N_NEIGHBORS = 5;

    Sensor* target = sensorDAO.getSensorById( sensorId );

    // Trouver les N voisins fiables les plus proches
    vector<Sensor> allSensors = sensorDAO.getAllSensors();
    vector<pair<double, string>> distances;
    for ( const Sensor& s : allSensors )
    {
        if ( s.getSensorId() == sensorId || !s.getIsReliable() ) continue;
        double d = haversineKm( target->getLatitude(), target->getLongitude(),
                                s.getLatitude(), s.getLongitude() );
        distances.push_back( { d, s.getSensorId() } );
    }
    sort( distances.begin(), distances.end() );
    int nNeighbors = min( N_NEIGHBORS, (int) distances.size() );

    // Collecter toutes les valeurs des voisins par attribut
    map<string, vector<double>> neighborVals;
    for ( int i = 0; i < nNeighbors; i++ )
    {
        vector<Measurement> meas = measurementDAO.getBySensor( distances[i].second, "", "" );
        for ( const Measurement& m : meas )
        {
            if ( m.getIsValid() )
                neighborVals[ m.getAttributeId() ].push_back( m.getValue() );
        }
    }

    // Moyenne et écart-type des voisins par attribut
    map<string, double> neighborMean, neighborStd;
    for ( auto& kv : neighborVals )
    {
        double mean = accumulate( kv.second.begin(), kv.second.end(), 0.0 )
                      / kv.second.size();
        neighborMean[ kv.first ] = mean;
        neighborStd [ kv.first ] = stdDev( kv.second );
    }

    // Calculer les z-scores pour le capteur cible
    vector<Measurement> targetMeas = measurementDAO.getBySensor( sensorId, "", "" );
    map<string, vector<double>> zscores;
    for ( const Measurement& m : targetMeas )
    {
        const string& attr = m.getAttributeId();
        if ( neighborStd[ attr ] < 1e-9 ) continue;
        double z = abs( m.getValue() - neighborMean[ attr ] ) / neighborStd[ attr ];
        zscores[ attr ].push_back( z );
    }

    // Score global = moyenne des z-scores par attribut
    map<string, double> avgDev;
    double totalScore = 0.0;
    int    attrCount  = 0;
    for ( auto& kv : zscores )
    {
        double mean = accumulate( kv.second.begin(), kv.second.end(), 0.0 )
                      / kv.second.size();
        avgDev[ kv.first ] = mean;
        totalScore += mean;
        attrCount++;
    }

    double score      = ( attrCount > 0 ) ? totalScore / attrCount : 0.0;
    bool   isReliable = ( score <= THRESHOLD );

    if ( !isReliable )
    {
        sensorDAO.markUnreliable( sensorId );
        PrivateUser* user = userDAO.getBySensorId( sensorId );
        if ( user != nullptr )
            user->blockPointAccumulation();
    }

    auto t_end = chrono::high_resolution_clock::now();
    long dur = chrono::duration_cast<chrono::milliseconds>( t_end - t_start ).count();

    return { sensorId, score, isReliable, avgDev, dur };
}
