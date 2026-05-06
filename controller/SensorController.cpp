#include "SensorController.h"
#include "../data/SensorDAO.h"
#include "../model/Sensor.h"
#include "../service/SensorAnalysisService.h"
#include <string>

SensorController::SensorController() {}

SensorController::~SensorController() {}

ReliabilityReport SensorController::handleAnalyzeReliability(string sensorId) {
    SensorDAO *sensorDAO = new SensorDAO();
    MeasurementDAO *measurementDAO = new MeasurementDAO();
    UserDAO *userDAO = new UserDAO();

    Sensor sensor = sensorDAO->getSensorById(sensorId);

    delete sensorDAO;

    if (!sensor.isPrivate()) {
        // return exception of null reliability report
        return ReliabilityReport{};
    }

    SensorAnalysisService *service = new SensorAnalysisService(*sensorDAO, *measurementDAO, *userDAO);

    ReliabilityReport report = service->analyzeReliability(sensorId);

    delete service;

    return report;
}
