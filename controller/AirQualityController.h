#include <vector>
#include <utility>
#include <string>
#include "../service/AirQualityService.h"

using namespace std;

class AirQualityController
{
public:
    AtmoResult handleComputeZone(string userId, int lat, int lon, int radius, string from, string to);
    AtmoResult handleComputePoint(string userId, int lat, int lon, string from, string to);
    vector<pair<string, double>> handleRankSensors(string sensorId, string from, string to);
    AirQualityController();
    ~AirQualityController();

private:

};
