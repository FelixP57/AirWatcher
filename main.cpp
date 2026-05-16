#include <iostream>
#include "data/CleanerDAO.h"
#include "data/MeasurementDAO.h"

void testCleanerDAO() {
    
    CleanerDAO cleanerDAO;
    printf("Loading providers and cleaners from CSV files...\n");
    cleanerDAO.loadCleanersFromCSV("dataset/cleaners.csv");
    printf("Cleaners loaded successfully.\n");
    cleanerDAO.loadProvidersFromCSV("dataset/providers.csv");
    printf("Providers loaded successfully.\n");

    // Exemple d'utilisation de la méthode getCleanerById
    cout << "Testing getCleanerById method..." << endl;
    Cleaner* cleaner = cleanerDAO.getCleanerById("Cleaner1");
    if (cleaner == nullptr) {
        cout << "Cleaner not found." << endl;
    } else {
        cout << "Cleaner ID: " << cleaner->getCleanerId() << endl;
        cout << "Latitude: " << cleaner->getLatitude() << ", Longitude: " << cleaner->getLongitude() << endl;
        cout << "Time Start: " << cleaner->getTimestampStart() << ", Time Stop: " << cleaner->getTimestampStop() << endl;
        cout << "Provider ID: " << cleaner->getProviderId() << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing getNearByCleaners method..." << endl;
    vector<Cleaner> nearbyCleaners = cleanerDAO.getNearByCleaners(45.333333, 1.333333, 1.0);
    for (const auto& cleaner : nearbyCleaners) {
        cout << "Nearby Cleaner ID: " << cleaner.getCleanerId() << endl;
        cout << "Latitude: " << cleaner.getLatitude() << endl;
        cout << "Longitude: " << cleaner.getLongitude() << endl;
        cout << "Time Start: " << cleaner.getTimestampStart() << endl;
        cout << "Time Stop: " << cleaner.getTimestampStop() << endl;
        cout << "Provider ID: " << cleaner.getProviderId() << endl;
    }
}

void testMeasurementDAO() {
    MeasurementDAO measurementDAO;
    printf("Loading measurements from CSV file...\n");
    measurementDAO.loadMeasurementsFromCSV("dataset/measurements.csv");
    printf("Measurements loaded successfully.\n");

    cout << "------------------------------" << endl;
    cout << "Testing getMeasurements method..." << endl;
    vector<Measurement> measurements = measurementDAO.getMeasurements("Sensor0", "2019-01-01 00:00:00", "2019-12-31 23:59:59");
    
    for (const auto& measurement : measurements) {
        cout << "Measurement - Timestamp: " << measurement.getTimestamp() << endl;
        cout << "Sensor ID: " << measurement.getSensorId() << endl;
        cout << "Attribute ID: " << measurement.getAttributeId() << endl;
        cout << "Value: " << measurement.getValue() << endl;
        cout << "Is Valid: " << measurement.getIsValid() << endl;
        cout << "-------------------------------" << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing getValidMeasurements method..." << endl;
    vector<Measurement> validMeasurements = measurementDAO.getValidMeasurements({"Sensor0"}, "2019-01-01 00:00:00", "2019-12-31 23:59:59");
    
    for (const auto& measurement : validMeasurements) {
        cout << "Measurement - Timestamp: " << measurement.getTimestamp() << endl;
        cout << "Sensor ID: " << measurement.getSensorId() << endl;
        cout << "Attribute ID: " << measurement.getAttributeId() << endl;
        cout << "Value: " << measurement.getValue() << endl;
        cout << "Is Valid: " << measurement.getIsValid() << endl;
        cout << "-------------------------------" << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing addMeasurements method..." << endl;
    Measurement newMeasurement("2020-01-01 12:00:00", "Sensor0", "Attribute0", 42.0, false);
    measurementDAO.appendMeasurement(newMeasurement);
    vector<Measurement> updatedMeasurements = measurementDAO.getMeasurements("Sensor0", "2020-01-01 00:00:00", "2020-12-31 23:59:59");

    for (const auto& measurement : updatedMeasurements) {
        cout << "Measurement - Timestamp: " << measurement.getTimestamp() << endl;
        cout << "Sensor ID: " << measurement.getSensorId() << endl;
        cout << "Attribute ID: " << measurement.getAttributeId() << endl;
        cout << "Value: " << measurement.getValue() << endl;
        cout << "Is Valid: " << measurement.getIsValid() << endl;
        cout << "-------------------------------" << endl;
    }
}

int main() {
    // testCleanerDAO();
    // testMeasurementDAO();

    return 0;
}