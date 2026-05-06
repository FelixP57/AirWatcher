#include "CleanerController.h"
#include "../service/CleanerService.h"
#include "../data/CleanerDAO.h"
#include "../data/SensorDAO.h"
#include "../data/MeasurementDAO.h"

CleanerController::CleanerController() {}

CleanerController::~CleanerController() {}

ImpactReport CleanerController::handleEvaluateImpact(string cleanerId) {
    SensorDAO *sensorDAO = new SensorDAO();
    MeasurementDAO *measurementDAO = new MeasurementDAO();
    CleanerDAO *cleanerDAO = new CleanerDAO();

    CleanerService *service = new CleanerService(*cleanerDAO, *sensorDAO, *measurementDAO);

    ImpactReport report = service->evaluateImpact(cleanerId);

    delete service;

    return report;
}