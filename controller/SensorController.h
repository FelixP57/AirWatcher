#ifndef SENSOR_CONTROLLER_H
#define SENSOR_CONTROLLER_H

#include "../service/SensorAnalysisService.h"
#include <string>

class SensorController
{
public:
    ReliabilityReport handleAnalyzeReliability(string sensorId);
    SensorController();
    ~SensorController();

private:
    
};

#endif