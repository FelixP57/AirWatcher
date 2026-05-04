
#if !defined ( CLEANERSERVICE_H )
#define CLEANERSERVICE_H

#include "../data/CleanerDAO.h"
#include "../data/SensorDAO.h"
#include "../data/MeasurementDAO.h"
#include "../model/Attribute.h"
#include <string>
#include <map>
using namespace std;

struct ImpactReport {
    string cleanerId;
    double atmoAvant;      // ATMO moyen 7j avant activation
    double atmoPendant;    // ATMO moyen pendant opération
    double delta;          // atmoAvant - atmoPendant (> 0 = amélioration)
    double effectiveRadius;
    long   durationMs;
};

class CleanerService
{
public:
    CleanerService ( CleanerDAO& cleanerDAO,
                     SensorDAO& sensorDAO,
                     MeasurementDAO& measurementDAO );

    // UC6 — évaluer l'impact d'un purificateur
    ImpactReport evaluateImpact ( const string& cleanerId );

private:
    double computeZoneMeanAtmo ( double lat, double lon, double radiusKm,
                                  const string& from, const string& to );
    double computeAtmoIndex    ( const map<string, double>& readings );
    static string subtractDays ( const string& timestamp, int days );

    CleanerDAO&     cleanerDAO;
    SensorDAO&      sensorDAO;
    MeasurementDAO& measurementDAO;
    map<string, Attribute> attributes; // O3, SO2, NO2, PM10
};

#endif // CLEANERSERVICE_H
