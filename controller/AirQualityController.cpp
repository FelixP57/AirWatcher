#include <ctime>
#include <string>
#include <tuple>
#include "AirQualityController.h"
#include "../service/AirQualityService.h"
#include "../service/SensorAnalysisService.h"
#include "../service/PointsService.h"

AirQualityController::AirQualityController() {}

AirQualityController::~AirQualityController() {}

AtmoResult AirQualityController::handleComputeZone(string userId, int lat, int lon, int radius, string from, string to) {   
    AirQualityService airService = new AirQualityService();
    
    AtmoResult meanAtmo = service.computeMeanAtmo(lat, lon, radius, from, to);

    delete airService;

    PointsService pointsService = new PointsService();
    pointsService.awardPoints(meanAtmo.get(2), userId);

    delete pointsService;

    return meanAtmo;
}

AtmoResult AirQualityController::handleComputePoint(string userId, int lat, int lon, int radius, string from, string to) {   
    AirQualityService airService = new AirQualityService();
    
    AtmoResult meanAtmo = service.computeMeanAtmo(lat, lon, radius, from, to);

    delete airService;

    PointsService pointsService = new PointsService();
    pointsService.awardPoints(meanAtmo.sensorIds, userId);

    delete pointsService;

    return meanAtmo;
}

vector<pair<string, double>> handleRankSensors(string sensorId, string from, string to) {
    SensorAnalysisService service = new SensorAnalysisService();

    vector<pair<string, double>> result = service.rankBySimilarity(sensorId, from, to);

    delete service;

    return result;
}