
#if !defined ( AIRQUALITYSERVICE_H )
#define AIRQUALITYSERVICE_H

#include "../data/SensorDAO.h"
#include "../data/MeasurementDAO.h"
#include "../model/Attribute.h"
#include "PointsService.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

struct AtmoResult {
    double atmoMean;   // indice ATMO moyen, -1 si pas de données
    long   durationMs;
};

struct PointAtmoResult {
    double atmoValue;  // indice ATMO interpolé, -1 si pas de données
    long   durationMs;
};

class AirQualityService
{
public:
    AirQualityService ( SensorDAO& sensorDAO,
                        MeasurementDAO& measurementDAO,
                        PointsService& pointsService );

    // UC2 — indice ATMO moyen dans une zone circulaire
    // from/to : "2019-01-01 12:00:00", chaîne vide = pas de filtre
    AtmoResult computeMeanAtmo ( double lat, double lon, double radiusKm,
                                 const string& from, const string& to );

    // UC3 — indice ATMO à un point précis (interpolation IDW)
    PointAtmoResult computeAtmoAtPoint ( double lat, double lon,
                                         const string& timestamp );

    // Utilisable par CleanerService
    static double haversineKm ( double lat1, double lon1,
                                 double lat2, double lon2 );

private:
    double computeAtmoIndex        ( const map<string, double>& readings );
    double computeMeanAtmoForSensor ( const string& sensorId,
                                      const string& from, const string& to );

    SensorDAO&      sensorDAO;
    MeasurementDAO& measurementDAO;
    PointsService&  pointsService;
    map<string, Attribute> attributes; // O3, SO2, NO2, PM10
};

#endif // AIRQUALITYSERVICE_H
