#include "CleanerController.h"
#include "../service/CleanerService.h"

CleanerController::CleanerController() {}

CleanerController::~CleanerController() {}

ImpactReport CleanerController::handleEvaluateImpact(string cleanerId) {
    CleanerService service = new CleanerService();

    ImpactReport report = service.evaluateImpact(cleanerId);

    delete service;

    return report;
}