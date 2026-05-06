
#include "CleanerService.h"
#include "../model/Sensor.h"
#include "../model/Measurement.h"
#include "../model/Cleaner.h"
#include <cmath>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <vector>
using namespace std;

CleanerService::CleanerService ( CleanerDAO& cleanerDAO,
                                  SensorDAO& sensorDAO,
                                  MeasurementDAO& measurementDAO )
    : cleanerDAO(cleanerDAO),
      sensorDAO(sensorDAO),
      measurementDAO(measurementDAO)
{
    attributes.insert( { "O3",   Attribute( "O3",   "µg/m3", "concentration d'ozone" ) } );
    attributes.insert( { "SO2",  Attribute( "SO2",  "µg/m3", "concentration de dioxyde de soufre" ) } );
    attributes.insert( { "NO2",  Attribute( "NO2",  "µg/m3", "concentration de dioxyde d'azote" ) } );
    attributes.insert( { "PM10", Attribute( "PM10", "µg/m3", "concentration de particules fines" ) } );
}

string CleanerService::subtractDays ( const string& timestamp, int days )
{
    struct tm t = {};
    sscanf( timestamp.c_str(), "%d-%d-%d %d:%d:%d",
            &t.tm_year, &t.tm_mon, &t.tm_mday,
            &t.tm_hour, &t.tm_min, &t.tm_sec );
    t.tm_year -= 1900;
    t.tm_mon  -= 1;
    t.tm_mday -= days;
    mktime( &t );

    char buf[20];
    strftime( buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &t );
    return string( buf );
}

double CleanerService::computeAtmoIndex ( const map<string, double>& readings )
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

double CleanerService::computeZoneMeanAtmo ( double lat, double lon, double radiusKm,
                                              const string& from, const string& to )
{
    vector<Sensor> sensors = sensorDAO.getSensorsInZone( lat, lon, radiusKm );

    double sum   = 0.0;
    int    count = 0;

    for ( const Sensor& s : sensors )
    {
        if ( !s.getIsReliable() ) continue;

        vector<Measurement> meas = measurementDAO.getBySensor( s.getSensorId(), from, to );

        map<string, map<string, double>> groups;
        for ( const Measurement& m : meas )
        {
            if ( m.getIsValid() )
                groups[ m.getTimestamp() ][ m.getAttributeId() ] = m.getValue();
        }

        for ( auto& ts_readings : groups )
        {
            if ( ts_readings.second.size() == 4 )
            {
                sum += computeAtmoIndex( ts_readings.second );
                count++;
            }
        }
    }
    return ( count > 0 ) ? sum / count : -1.0;
}

ImpactReport CleanerService::evaluateImpact ( const string& cleanerId )
{
    auto t_start = chrono::high_resolution_clock::now();
    const double RADIUS_KM         = 10.0;
    const int    BEFORE_WINDOW_DAYS = 7;

    Cleaner* cleaner = cleanerDAO.getById( cleanerId );
    if ( cleaner == nullptr )
    {
        return { cleanerId, -1.0, -1.0, 0.0, RADIUS_KM, 0 };
    }

    string beforeEnd   = cleaner->getTimestampStart();
    string beforeStart = subtractDays( beforeEnd, BEFORE_WINDOW_DAYS );
    string duringStart = cleaner->getTimestampStart();
    string duringEnd   = cleaner->getTimestampStop();

    double atmoAvant   = computeZoneMeanAtmo( cleaner->getLatitude(), cleaner->getLongitude(),
                                               RADIUS_KM, beforeStart, beforeEnd );
    double atmoPendant = computeZoneMeanAtmo( cleaner->getLatitude(), cleaner->getLongitude(),
                                               RADIUS_KM, duringStart, duringEnd );

    double delta = ( atmoAvant >= 0 && atmoPendant >= 0 ) ? atmoAvant - atmoPendant : 0.0;

    auto t_end = chrono::high_resolution_clock::now();
    long dur = chrono::duration_cast<chrono::milliseconds>( t_end - t_start ).count();

    return { cleanerId, atmoAvant, atmoPendant, delta, RADIUS_KM, dur };
}
