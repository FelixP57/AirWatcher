/*************************************************************************
                           CleanerDAO  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <CleanerDAO> (fichier CleanerDAO.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "CleanerDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type CleanerDAO::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
CleanerDAO::CleanerDAO ( const CleanerDAO & unCleanerDAO )
// Algorithme :
//
{
        this->cleaners = unCleanerDAO.cleaners;
        this->providers = unCleanerDAO.providers;
#ifdef MAP
    cout << "Appel au constructeur de copie de <CleanerDAO>" << endl;
#endif
} //----- Fin de CleanerDAO (constructeur de copie)


CleanerDAO::CleanerDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <CleanerDAO>" << endl;
#endif
} //----- Fin de CleanerDAO


CleanerDAO::~CleanerDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CleanerDAO>" << endl;
#endif
} //----- Fin de ~CleanerDAO

void CleanerDAO::loadCleanersFromCSV(string filename) {
        // Implémentation de la lecture du fichier CSV et de la création des objets Cleaner
        
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            // Lecture et traitement des lignes du fichier
            cout << "Cleaner's data file opened successfully." << endl;
            cout << "------------------------------" << endl;

            while (!file.eof()) {

                if (file.peek() == EOF) {
                    break; // Exit the loop if we have reached the end of the file
                }

                string cleanerId, timeStart, timeStop, providerId;
                double longitude, latitude;

                // Read the line and store cleaner's ID
                cout << "Reading cleaner data..." << endl;
                getline(file, line, ';');
                cleanerId = line;
                cout << "Cleaner ID: " << cleanerId << endl;

                // Read the line and store cleaner's longitude and latitude
                getline(file, line, ';');
                latitude = stod(line);
                getline(file, line, ';');
                longitude = stod(line);
                cout << "Longitude: " << longitude << ", Latitude: " << latitude << endl;

                // Read the line and store cleaner's time start and time stop
                getline(file, line, ';');
                timeStart = line;
                getline(file, line, ';');
                timeStop = line;
                cout << "Time Start: " << timeStart << ", Time Stop: " << timeStop << endl;

                // Read the line to get rid of the newline character
                getline(file, line, '\n');

                // Store provider's ID
                providerId = "";
                Cleaner cleaner = Cleaner(cleanerId, longitude, latitude, timeStart, timeStop, providerId);
                cout << cleanerId << " created successfully." << endl;
                cout << "------------------------------" << endl;
                cleaners.insert(pair<string, Cleaner>(cleanerId, cleaner));
                cout << "Number of cleaners: " << cleaners.size() << endl;
                for (const auto& pair : cleaners) {
                    cout << "Cleaner ID: " << pair.first << endl;
                }
                cout << "------------------------------" << endl; 
            }

        }
    }

void CleanerDAO::loadProvidersFromCSV(string filename) {
        // Implémentation de la lecture du fichier CSV et de la création des objets Provider
        
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            // Lecture et traitement des lignes du fichier
            while (!file.eof()) {

                if (file.peek() == EOF) {
                    break; // Exit the loop if we have reached the end of the file
                }

                string providerId, cleanerId;

                cout << "Reading provider data..." << endl;
                cout << "------------------------------" << endl;

                getline(file, line, ';');
                providerId = line;
                cout << "Provider ID: " << providerId << endl;

                getline(file, line, ';');
                cleanerId = line;
                cout << "Cleaner ID: " << cleanerId << endl;

                // Read the line to get rid of the newline character
                getline(file, line, '\n');

                Cleaner* cleaner = getCleanerById(cleanerId);
                if (cleaner != nullptr) {
                    cleaner->setProviderId(providerId);
                    cout << "Cleaner " << cleanerId << " is associated with Provider " << providerId << endl;
                } else {
                    Cleaner cleaner = Cleaner(cleanerId, 0.0, 0.0, "", "", providerId);
                }

                cout << "------------------------------" << endl;

                if (providers.find(providerId) == providers.end()) {
                    // If there is no provider with this ID, create a new one
                    vector<string> cleanerIds = {cleanerId};
                    Provider provider(providerId, "", "", Role::PROVIDER, cleanerIds);
                    providers.insert(pair<string, Provider>(providerId, provider));
                } else {
                    // Get the existing provider vector of cleaner IDs
                    vector<string> cleanerIds = providers.at(providerId).getCleanerIds();
                    // Add the new cleaner ID to the vector
                    cleanerIds.push_back(cleanerId);
                    // Update the provider with the new vector of cleaner IDs
                    providers.at(providerId).setCleanerIds(cleanerIds);
                }

            }

        }
    }

Cleaner* CleanerDAO::getCleanerById(string cleanerId) {
        // Implémentation de la récupération d'un Cleaner par son ID
        if (cleaners.find(cleanerId) != cleaners.end()) {
            cout << "Cleaner " << cleanerId << " found." << endl;
            return &(cleaners.at(cleanerId));
        } else {
            return nullptr;
        }        
    }

vector<Cleaner> CleanerDAO::getNearByCleaners(double longitude, double latitude, double radius) {
        vector<Cleaner> nearbyCleaners;
        
        for (const auto& pair : cleaners) {
            const Cleaner& cleaner = pair.second;
            double distance = computeDistance(longitude, latitude, cleaner.getLongitude(), cleaner.getLatitude());
            if (distance <= radius) {
                nearbyCleaners.push_back(cleaner);
            }
        }
        return nearbyCleaners;
    }

double CleanerDAO::computeDistance(double lon1, double lat1, double lon2, double lat2) {
        // On suppose qu'il s'agit d'une surface euclidienne pour simplifier le calcul de distance
        double distance = sqrt(pow(lon2 - lon1, 2) + pow(lat2 - lat1, 2));
        return distance;
    }

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées