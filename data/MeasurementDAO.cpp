/*************************************************************************
                           MeasurementDAO  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <MeasurementDAO> (fichier MeasurementDAO.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "MeasurementDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type MeasurementDAO::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void MeasurementDAO::loadMeasurementsFromCSV(string filename) {

    ifstream file(filename);
    string line;

    if (file.is_open()) {
        int data = 0;
        while (!file.eof()) {

            if (file.peek() == EOF) {
                break; // Exit the loop if we have reached the end of the file
            }

            cout << "-------------------------------" << endl;
            cout << "Reading measurement data..." << endl;

            getline(file, line, ';');
            string timestamp = line;
            cout << "Timestamp: " << timestamp << endl;

            getline(file, line, ';');
            string sensorId = line;
            cout << "Sensor ID: " << sensorId << endl;

            getline(file, line, ';');
            string attributeId = line;
            cout << "Attribute ID: " << attributeId << endl;

            getline(file, line, ';');
            double value = stod(line);
            cout << "Value: " << value << endl;

            getline(file, line, '\n'); // Get rid of the newline character

            if (data % 2 == 0) {
                Measurement measurement(timestamp, sensorId, attributeId, value, true);
                measurements.push_back(measurement);
            } else {
                Measurement measurement(timestamp, sensorId, attributeId, value, false);
                measurements.push_back(measurement);
            }

            cout << "-------------------------------" << endl;

            data+= 1;
            if (data == 3) {
                break; // Stop after reading 3 lines of data
            }

        }
    }

    /*for (const auto& m : measurements) {
                cout << "Measurement - Timestamp: " << m.getTimestamp() << endl;
                cout << "Sensor ID: " << m.getSensorId() << endl;
                cout << "Attribute ID: " << m.getAttributeId() << endl;
                cout << "Value: " << m.getValue() << endl;
                cout << "Is Valid: " << m.getIsValid() << endl;
                cout << "-------------------------------" << endl;
            }*/

    file.close();
}

void MeasurementDAO::loadAttributesFromCSV(string filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (!file.eof()) {

            if (file.peek() == EOF) {
                break; // Exit the loop if we have reached the end of the file
            }

            cout << "-------------------------------" << endl;
            cout << "Reading attribute data..." << endl;

            getline(file, line, ';');
            string attributeId = line;
            cout << "Attribute ID: " << attributeId << endl;

            getline(file, line, ';');
            string unit = line;
            cout << "Unit: " << unit << endl;

            getline(file, line, ';');
            string description = line;
            cout << "Description: " << description << endl;

            getline(file, line, '\n'); // Get rid of the newline character

            cout << "-------------------------------" << endl;

        }
    }

    file.close();
}

vector<Measurement> MeasurementDAO::getMeasurements(string sensorId, string from, string to) {
    vector<Measurement> allMeasurements;
    Date fromDate = parseDate(from);
    Date toDate = parseDate(to);

    for (const auto& measurement : measurements) {
        if (measurement.getSensorId() == sensorId) {
            Date measurementDate = parseDate(measurement.getTimestamp());
            // cout << "Parsing date successful" << endl;
            // cout << "--------------------------------" << endl;
            if (compareDates(fromDate, measurementDate) \
            && compareDates(measurementDate, toDate)) {
                allMeasurements.push_back(measurement);
            }
        }
    }
    return allMeasurements;
}

vector<Measurement> MeasurementDAO::getValidMeasurements(vector<string> sensorIds, string from, string to) {
    vector<Measurement> validMeasurements;
    Date fromDate = parseDate(from);
    Date toDate = parseDate(to);

    for (const auto& measurement : measurements) {
        int position = 0;
        while (position < (int)sensorIds.size()) {
            if (measurement.getSensorId() == sensorIds[position]) {
                if (measurement.getIsValid()) {

                    Date measurementDate = parseDate(measurement.getTimestamp());
                    // cout << "Parsing date successful" << endl;
                    // cout << "--------------------------------" << endl;

                    if (compareDates(fromDate, measurementDate) \
                        && compareDates(measurementDate, toDate)) {
                            validMeasurements.push_back(measurement);
                    }
                }
                break; // Exit the loop once a match is found
            } else {
                position += 1;
            }
        }
    }
    return validMeasurements;
}

Date MeasurementDAO::parseDate(const string& timestamp) {
    Date parsedDate;
    //cout << "Parsing date from timestamp: " << timestamp << endl;
    parsedDate.year = stoi(timestamp.substr(0, 4));
    parsedDate.month = stoi(timestamp.substr(5, 2));
    parsedDate.day = stoi(timestamp.substr(8, 2));
    parsedDate.hour = stoi(timestamp.substr(11, 2));
    parsedDate.minute = stoi(timestamp.substr(14, 2));
    parsedDate.second = stoi(timestamp.substr(17, 2));
    return parsedDate;
}

bool MeasurementDAO::compareDates(const Date& date1, const Date& date2) {
    if (date1.year != date2.year) {
        return date1.year < date2.year;
    } else if (date1.month != date2.month) {
        return date1.month < date2.month;
    } else if (date1.day != date2.day) {
        return date1.day < date2.day;
    } else if (date1.hour != date2.hour) {
        return date1.hour < date2.hour;
    } else if (date1.minute != date2.minute) {
        return date1.minute < date2.minute;
    } else if (date1.second != date2.second) {
        return date1.second < date2.second;
    } else {
        return true; // Les deux dates sont égales
    }
}

void MeasurementDAO::appendMeasurement(const Measurement& measurement) {
    measurements.push_back(measurement);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
MeasurementDAO::MeasurementDAO ( const MeasurementDAO & unMeasurementDAO )
// Algorithme :
//
{
    this->measurements = unMeasurementDAO.measurements;
#ifdef MAP
    cout << "Appel au constructeur de copie de <MeasurementDAO>" << endl;
#endif
} //----- Fin de MeasurementDAO (constructeur de copie)


MeasurementDAO::MeasurementDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <MeasurementDAO>" << endl;
#endif
} //----- Fin de MeasurementDAO


MeasurementDAO::~MeasurementDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <MeasurementDAO>" << endl;
#endif
} //----- Fin de ~MeasurementDAO

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées