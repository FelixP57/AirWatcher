#include <iostream>
#include "data/CleanerDAO.h"
#include "data/MeasurementDAO.h"
#include "data/UserDAO.h"
#include "data/SensorDAO.h"
using namespace std;

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

void testUserDAO() {
    UserDAO userDAO;
    printf("Loading users from CSV file...\n");
    userDAO.loadUsersFromCSV("dataset/users.csv");
    printf("Users loaded successfully.\n");

    cout << "------------------------------" << endl;
    cout << "Testing authenticate method for User0..." << endl;
    // User* user = userDAO.authenticate("User0", "123");
    User* user = userDAO.authenticate("User0", "145"); // Wrong password test

    cout << "Authentication result for User0 with password '145' (wrong one): " << endl;
    if (user != nullptr) {
        cout << "User ID: " << user->getUserId() << endl;
        cout << "Login: " << user->getLogin() << endl;
        cout << "Role: " << (user->getRole() == Role::USER ? "USER" : "ADMIN") << endl;
    } else {
        cout << "Authentication failed." << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing getUserById method for User1..." << endl;
    User* userById = userDAO.getUserById("User1");
    if (userById != nullptr) {
        cout << "User ID: " << userById->getUserId() << endl;
        cout << "Login: " << userById->getLogin() << endl;
        cout << "Role: " << (userById->getRole() == Role::USER ? "USER" : "ADMIN") << endl;
    } else {
        cout << "User not found." << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing addUser method for User2..." << endl;
    userDAO.addUser(new PrivateUser("User2", "Sensor0", "User2", "password", Role::ADMIN));
    if (userDAO.getUserById("User2") != nullptr) {
        cout << "User2 added successfully." << endl;
        cout << "User ID: " << userDAO.getUserById("User2")->getUserId() << endl;
        cout << "Login: " << userDAO.getUserById("User2")->getLogin() << endl;
        cout << "Role: " << userDAO.getUserById("User2")->getRole() << endl;
        cout << "Password: " << userDAO.getUserById("User2")->getHashedPassword() << endl;
        cout << "Points: " << dynamic_cast<PrivateUser*>(userDAO.getUserById("User2"))->getPoints() << endl;
    } else {
        cout << "Failed to add User2." << endl;
    } 

    cout << "------------------------------" << endl;
    cout << "Testing updatePoints method for User2..." << endl;
    userDAO.updatePoints("User2", 10);
    PrivateUser* updatedUser = dynamic_cast<PrivateUser*>(userDAO.getUserById("User2"));
    if (updatedUser != nullptr) {
        cout << "User2 points updated successfully." << endl;
        cout << "User ID: " << updatedUser->getUserId() << endl;
        cout << "Points: " << updatedUser->getPoints() << endl;
        cout << "Is Blocked: " << updatedUser->getIsBlocked() << endl;
    } else {
        cout << "Failed to update points for User2." << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing blockUser method for User2..." << endl;
    userDAO.blockUser("User2");
    PrivateUser* blockedUser = dynamic_cast<PrivateUser*>(userDAO.getUserById("User2"));
    if (blockedUser != nullptr) {
        cout << "User2 blocked successfully." << endl;
        cout << "User ID: " << blockedUser->getUserId() << endl;
        cout << "Is Blocked: " << blockedUser->getIsBlocked() << endl;
    } else {
        cout << "Failed to block User2." << endl;
    }
    userDAO.updatePoints("User2", 10); // Try to update points for a blocked user
    PrivateUser* blockedUserAfterPointsUpdate = dynamic_cast<PrivateUser*>(userDAO.getUserById("User2"));
    if (blockedUserAfterPointsUpdate != nullptr) {
        cout << "User2 points after update attempt: " << blockedUserAfterPointsUpdate->getPoints() << endl;
    } else {
        cout << "Failed to retrieve User2 after points update attempt." << endl;
    }

}

void testSensorDAO() {
    SensorDAO sensorDAO;
    printf("Loading sensors from CSV file...\n");
    sensorDAO.loadSensorsFromCSV("dataset/sensors.csv");
    printf("Sensors loaded successfully.\n");

    cout << "------------------------------" << endl;
    cout << "Testing getSensorById method..." << endl;
    Sensor* sensor = sensorDAO.getSensorById("Sensor5");
    if (sensor != nullptr) {
        cout << "Sensor ID: " << sensor->getSensorId() << endl;
        cout << "Latitude: " << sensor->getLatitude() << ", Longitude: " << sensor->getLongitude() << endl;
    } else {
        cout << "Sensor not found." << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing getSensorsInCircle method..." << endl;
    vector<Sensor> nearbySensors = sensorDAO.getSensorsInCircle(44, 1.1, 1);
    for (const auto& sensor : nearbySensors) {
        cout << "Nearby Sensor ID: " << sensor.getSensorId() << endl;
        cout << "Latitude: " << sensor.getLatitude() << endl;
        cout << "Longitude: " << sensor.getLongitude() << endl;
        cout << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing markUnreliable method..." << endl;
    Sensor* unreliableSensor = sensorDAO.getSensorById("Sensor5");
    if (unreliableSensor != nullptr) {
        cout << "Sensor5 reliable." << endl;
        cout << "Sensor ID: " << unreliableSensor->getSensorId() << endl;
        cout << "Is Reliable: " << unreliableSensor->getIsReliable() << endl;
        cout << endl;
        sensorDAO.markUnreliable("Sensor5");
        cout << "Sensor5 Is Reliable: " << unreliableSensor->getIsReliable() << endl;
    } else {
        cout << "Failed to mark Sensor5 as unreliable." << endl;
    }

    cout << "------------------------------" << endl;
    cout << "Testing addSensor method..." << endl;
    Sensor newSensor("Sensor100", 45.0, 1.0);
    sensorDAO.addSensor(newSensor);
    Sensor* addedSensor = sensorDAO.getSensorById("Sensor100");
    if (addedSensor != nullptr) {
        cout << "Sensor10 added successfully." << endl;
        cout << "Sensor ID: " << addedSensor->getSensorId() << endl;
        cout << "Latitude: " << addedSensor->getLatitude() << endl;
        cout << "Longitude: " << addedSensor->getLongitude() << endl;
    } else {
        cout << "Failed to add Sensor100." << endl;
    }
}

int main() {
    // testCleanerDAO();
    // testMeasurementDAO();
    testUserDAO();
    // testSensorDAO();

    return 0;
}