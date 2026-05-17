/*************************************************************************
                           SensorDAO  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <SensorDAO> (fichier SensorDAO.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "SensorDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type SensorDAO::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
SensorDAO::SensorDAO ( const SensorDAO & unSensorDAO )
// Algorithme :
//
{
        this->sensors = unSensorDAO.sensors;
#ifdef MAP
    cout << "Appel au constructeur de copie de <SensorDAO>" << endl;
#endif
} //----- Fin de SensorDAO (constructeur de copie)


SensorDAO::SensorDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <SensorDAO>" << endl;
#endif
} //----- Fin de SensorDAO


SensorDAO::~SensorDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <SensorDAO>" << endl;
#endif
} //----- Fin de ~SensorDAO

void SensorDAO::loadSensorsFromCSV(string filename) {
        // Implémentation de la lecture du fichier CSV et de la création des objets Sensor
        
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            // Lecture et traitement des lignes du fichier
            cout << "Sensor's data file opened successfully." << endl;
            cout << "------------------------------" << endl;

            while (!file.eof()) {

                if (file.peek() == EOF) {
                    break; // Exit the loop if we have reached the end of the file
                }

                getline(file, line, ';'); // Read the first field (Sensor ID)
                string sensorId = line;
                cout << "Sensor ID: " << sensorId << endl;

                getline(file, line, ';'); // Read the second field (Latitude)
                double latitude = stod(line);
                cout << "Latitude: " << latitude << endl;
                getline(file, line, ';'); // Read the third field (Longitude)
                double longitude = stod(line);
                cout << "Longitude: " << longitude << endl;

                cout << endl;
                cout << "------------------------------" << endl;
                cout << endl;

                // Read the line to get rid of the newline character
                getline(file, line, '\n');

                Sensor sensor(sensorId, latitude, longitude);
                sensors.insert(pair<string, Sensor>(sensorId, sensor));
            }

        }

        file.close();
    }

    Sensor* SensorDAO::getSensorById(const string id) {
        if (sensors.find(id) != sensors.end()) {
            return &sensors.find(id)->second; // Return a pointer to the Sensor object
        } else {
            return nullptr; // Sensor not found
        }
        
    }

    vector<Sensor> SensorDAO::getSensorsInCircle(double lat, double lon, double radius) {
        vector<Sensor> sensorsInCircle;
        for (const auto& pair : sensors) {
            Sensor sensor = pair.second;
            bool inCircle = inRadius(lat, lon, sensor.getLatitude(), sensor.getLongitude(), radius);
            if (inCircle) {
                sensorsInCircle.push_back(sensor);
            }
        }
        return sensorsInCircle;
    }

    bool SensorDAO::inRadius(double lat1, double lon1, double lat2, double lon2, double radius) {
        double distance = sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));
        if (distance <= radius) {
            return true;
        } else {
            return false;
        }
    }

    void SensorDAO::markUnreliable(string sensorId) {
        if (sensors.find(sensorId) != sensors.end()) {
            sensors.find(sensorId)->second.setIsReliable(false);
        }
    }

    void SensorDAO::addSensor(Sensor sensor) {
        sensors.insert(pair<string, Sensor>(sensor.getSensorId(), sensor));
    }

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées