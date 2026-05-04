
#include "AirQualityService.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include <cmath>
#include <chrono>
using namespace std;

static const double PI = 3.14159265358979323846;

AirQualityService::AirQualityService ( SensorDAO& sensorDAO,
                                        MeasurementDAO& measurementDAO,
                                        PointsService& pointsService )
    : sensorDAO(sensorDAO),
      measurementDAO(measurementDAO),
      pointsService(pointsService)
{
    attributes.insert( { "O3",   Attribute( "O3",   "µg/m3", "concentration d'ozone" ) } );
    attributes.insert( { "SO2",  Attribute( "SO2",  "µg/m3", "concentration de dioxyde de soufre" ) } );
    attributes.insert( { "NO2",  Attribute( "NO2",  "µg/m3", "concentration de dioxyde d'azote" ) } );
    attributes.insert( { "PM10", Attribute( "PM10", "µg/m3", "concentration de particules fines" ) } );
}

double AirQualityService::haversineKm ( double lat1, double lon1,
                                         double lat2, double lon2 )
{
    const double R = 6371.0;
    double dLat = ( lat2 - lat1 ) * PI / 180.0;
    double dLon = ( lon2 - lon1 ) * PI / 180.0;
    double a = sin( dLat / 2 ) * sin( dLat / 2 )
             + cos( lat1 * PI / 180.0 ) * cos( lat2 * PI / 180.0 )
             * sin( dLon / 2 ) * sin( dLon / 2 );
    return R * 2.0 * atan2( sqrt( a ), sqrt( 1.0 - a ) );
}

double AirQualityService::computeAtmoIndex ( const map<string, double>& readings )
{
    int maxIdx = 0;
    for ( auto& kv : readings )
    {
        auto it = attributes.find( kv.first );
        if ( it != attributes.end() )
        {
            int idx = it->second.computeAtmoIndex( kv.second );
            if ( idx > maxIdx ) maxIdx = idx;
        }
    }
    return (double) maxIdx;
}

double AirQualityService::computeMeanAtmoForSensor ( const string& sensorId,
                                                      const string& from,
                                                      const string& to )
{
    vector<Measurement> meas = measurementDAO.getBySensor( sensorId, from, to );

    // Grouper les mesures par timestamp
    map<string, map<string, double>> groups;
    for ( const Measurement& m : meas )
    {
        if ( m.getIsValid() )
            groups[ m.getTimestamp() ][ m.getAttributeId() ] = m.getValue();
    }

    double sum   = 0.0;
    int    count = 0;
    for ( auto& ts_readings : groups )
    {
        if ( ts_readings.second.size() == 4 )
        {
            sum += computeAtmoIndex( ts_readings.second );
            count++;
        }
    }
    return ( count > 0 ) ? sum / count : -1.0;
}

AtmoResult AirQualityService::computeMeanAtmo ( double lat, double lon, double radiusKm,
                                                 const string& from, const string& to )
{
    auto t_start = chrono::high_resolution_clock::now();

    vector<Sensor> sensors = sensorDAO.getSensorsInZone( lat, lon, radiusKm );

    double         sum    = 0.0;
    int            count  = 0;
    vector<string> usedIds;

    for ( const Sensor& s : sensors )
    {
        if ( !s.getIsReliable() ) continue;

        double atmo = computeMeanAtmoForSensor( s.getSensorId(), from, to );
        if ( atmo >= 0 )
        {
            sum += atmo;
            count++;
            usedIds.push_back( s.getSensorId() );
        }
    }

    if ( !usedIds.empty() )
        pointsService.awardPoints( usedIds );

    auto t_end = chrono::high_resolution_clock::now();
    long dur = chrono::duration_cast<chrono::milliseconds>( t_end - t_start ).count();

    return { ( count > 0 ) ? sum / count : -1.0, dur };
}

PointAtmoResult AirQualityService::computeAtmoAtPoint ( double lat, double lon,
                                                          const string& timestamp )
{
    auto t_start = chrono::high_resolution_clock::now();

    vector<Sensor> sensors = sensorDAO.getAllSensors();

    double weightedSum = 0.0;
    double totalWeight = 0.0;

    for ( const Sensor& s : sensors )
    {
        if ( !s.getIsReliable() ) continue;

        double dist = haversineKm( lat, lon, s.getLatitude(), s.getLongitude() );

        vector<Measurement> meas = measurementDAO.getClosestTo( s.getSensorId(), timestamp );
        map<string, double> readings;
        for ( const Measurement& m : meas )
        {
            if ( m.getIsValid() )
                readings[ m.getAttributeId() ] = m.getValue();
        }
        if ( readings.size() < 4 ) continue;

        double atmo = computeAtmoIndex( readings );

        // Capteur exactement à la position → retour direct sans interpolation
        if ( dist < 0.001 )
        {
            auto t_end = chrono::high_resolution_clock::now();
            long dur = chrono::duration_cast<chrono::milliseconds>( t_end - t_start ).count();
            return { atmo, dur };
        }

        double weight  = 1.0 / ( dist * dist );
        weightedSum   += weight * atmo;
        totalWeight   += weight;
    }

    auto t_end = chrono::high_resolution_clock::now();
    long dur = chrono::duration_cast<chrono::milliseconds>( t_end - t_start ).count();

    return { ( totalWeight > 0 ) ? weightedSum / totalWeight : -1.0, dur };
}
