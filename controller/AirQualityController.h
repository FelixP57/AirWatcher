#include <vector>
#include <utility>
#include <string>
#include "../service/AirQualityService.h"

using namespace std;

class AirQualityController
{
public:
    AtmoResult handleComputeZone(const string& userId, int lat, int lon, int radius, const string& from, const string& to);
    PointAtmoResult handleComputePoint(const string& userId, int lat, int lon, const string& timestamp);
    vector<SensorScore> handleRankSensors(const string& sensorId, const string& from, const string& to);
    AirQualityController();
    ~AirQualityController();

private:

};
