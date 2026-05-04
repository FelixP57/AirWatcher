
#if !defined ( SENSORANALYSISSERVICE_H )
#define SENSORANALYSISSERVICE_H

#include "../data/SensorDAO.h"
#include "../data/MeasurementDAO.h"
#include "../data/UserDAO.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

struct SensorScore {
    string sensorId;
    double score;      // distance euclidienne (0 = identique)
};

struct ReliabilityReport {
    string sensorId;
    double score;                        // z-score moyen (> 2.0 → non fiable)
    bool   isReliable;
    map<string, double> deviationByAttr; // "O3" → z-score moyen
    long   durationMs;
};

class SensorAnalysisService
{
public:
    SensorAnalysisService ( SensorDAO& sensorDAO,
                             MeasurementDAO& measurementDAO,
                             UserDAO& userDAO );

    // UC5 — classer tous les capteurs par similarité (score croissant)
    vector<SensorScore> rankBySimilarity ( const string& refSensorId,
                                           const string& from,
                                           const string& to );

    // UC4 — analyser la fiabilité d'un capteur privé
    // Si non fiable : marque le capteur et bloque les points
    ReliabilityReport analyzeReliability ( const string& sensorId );

private:
    map<string, double> computeAvgVector ( const string& sensorId,
                                           const string& from,
                                           const string& to );

    double euclideanDistance ( const map<string, double>& v1,
                               const map<string, double>& v2 );
    double stdDev            ( const vector<double>& values );
    static double haversineKm ( double lat1, double lon1,
                                 double lat2, double lon2 );

    SensorDAO&      sensorDAO;
    MeasurementDAO& measurementDAO;
    UserDAO&        userDAO;
};

#endif // SENSORANALYSISSERVICE_H
