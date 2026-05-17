//---------- Interface de la classe <SensorDAO> (fichier SensorDAO.h) ----------------
#if ! defined ( SENSORDAO_H )
#define SENSORDAO_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

#include "Sensor.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <SensorDAO>
//
//
//------------------------------------------------------------------------

class SensorDAO 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void loadSensorsFromCSV(string filename);

    Sensor* getSensorById(const string id);

    vector<Sensor> getSensorsInCircle(double lat, double lon, double radius);

    bool inRadius(double lat1, double lon1, double lat2, double lon2, double radius);

    void markUnreliable(string sensorId);

    void addSensor(Sensor sensor);

//-------------------------------------------- Constructeurs - destructeur
    SensorDAO ( const SensorDAO & unSensorDAO );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    SensorDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~SensorDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map<string, Sensor> sensors;

};

//-------------------------------- Autres définitions dépendantes de <SensorDAO>

#endif // SENSORDAO_H