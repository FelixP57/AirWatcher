#include <iostream>
#include "data/CleanerDAO.h"
int main() {
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


    return 0;
}