#include <ctime>
#include <string>
#include <tuple>
#include "AirQualityController.h"
#include "../service/AirQualityService.h"
#include "../service/SensorAnalysisService.h"
#include "../service/PointsService.h"
#include "../data/UserDAO.h"
#include "../data/SensorDAO.h"
#include "../data/MeasurementDAO.h"

AirQualityController::AirQualityController() {}

AirQualityController::~AirQualityController() {}

AtmoResult AirQualityController::handleComputeZone(const string& userId, int lat, int lon, int radius, const string& from, const string& to) {   
    SensorDAO *sensorDAO = new SensorDAO();
    MeasurementDAO *measurementDAO = new MeasurementDAO();
    UserDAO *userDAO = new UserDAO();

    PointsService *pointsService = new PointsService(*userDAO);
    AirQualityService *airService = new AirQualityService(*sensorDAO, *measurementDAO, *pointsService);
    
    AtmoResult meanAtmo = airService->computeMeanAtmo(lat, lon, radius, from, to);

    delete airService;
    delete measurementDAO;
    delete pointsService;

    return meanAtmo;
}

PointAtmoResult AirQualityController::handleComputePoint(const string& userId, int lat, int lon, const string& timestamp) {   
    SensorDAO *sensorDAO = new SensorDAO();
    MeasurementDAO *measurementDAO = new MeasurementDAO();
    UserDAO *userDAO = new UserDAO();

    PointsService *pointsService = new PointsService(*userDAO);
    AirQualityService *airService = new AirQualityService(*sensorDAO, *measurementDAO, *pointsService);
    
    PointAtmoResult pointAtmo = airService->computeAtmoAtPoint(lon, lat, timestamp);

    delete airService;
    delete measurementDAO;
    delete pointsService;

    return pointAtmo;
}

vector<SensorScore> handleRankSensors(const string& sensorId, const string& from, const string& to) {
    SensorDAO *sensorDAO = new SensorDAO();
    MeasurementDAO *measurementDAO = new MeasurementDAO();
    UserDAO *userDAO = new UserDAO();
    SensorAnalysisService *service = new SensorAnalysisService(*sensorDAO, *measurementDAO, *userDAO);

    vector<SensorScore> result = service->rankBySimilarity(sensorId, from, to);

    delete service;

    return result;
}