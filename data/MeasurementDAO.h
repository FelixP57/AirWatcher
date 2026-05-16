//---------- Interface de la classe <MeasurementDAO> (fichier MeasurementDAO.h) ----------------
#if ! defined ( MEASUREMENTDAO_H )
#define MEASUREMENTDAO_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../model/Measurement.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} Date;

//------------------------------------------------------------------------
// Rôle de la classe <MeasurementDAO>
//
//
//------------------------------------------------------------------------

class MeasurementDAO 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void loadMeasurementsFromCSV(string filename);

    vector<Measurement> getMeasurements(string sensorId, string from, string to);

    vector<Measurement> getValidMeasurements(vector<string> sensorIds, string from, string to);

    void appendMeasurement(const Measurement& measurement);

    Date parseDate(const string& timestamp);

    bool compareDates(const Date& date1, const Date& date2);

//-------------------------------------------- Constructeurs - destructeur
    MeasurementDAO ( const MeasurementDAO & unMeasurementDAO );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    MeasurementDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~MeasurementDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<Measurement> measurements;

};

//-------------------------------- Autres définitions dépendantes de <MeasurementDAO>

#endif // MEASUREMENTDAO_H