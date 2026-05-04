#include "SensorController.h"
#include "../data/SensorDAO.h"
#include "../model/Sensor.h"
#include "../service/SensorAnalysisService.h"
#include <string>

SensorController::SensorController() {}

SensorController::~SensorController() {}

ReliabilityReport SensorController::handleAnalyzeReliability(string sensorId) {
    SensorDAO sensorDAO = new SensorDAO();
    
    Sensor sensor = sensorDAO.getSensorById(sensorId);

    delete sensorDAO;

    if (!sensor.isPrivate()) {
        // return exception of null reliability report
        return nullptr;
    }

    SensorAnalysisService service = new SensorAnalysisService();

    ReliabilityReport report = service.analyzeReliability(sensorId);

    delete service;

    return report;
}

void SensorController::handleMarkUnreliable(string sensorId) {
    SensorAnalysisService service = new SensorAnalysisService();

    service.markUnreliable(sensorId);

    delete service;
}