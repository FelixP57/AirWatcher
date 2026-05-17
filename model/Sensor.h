/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( SENSOR_H )
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//
//------------------------------------------------------------------------

class Sensor 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    bool isPrivate ( );
    // Mode d'emploi : Vérifie si le sensor appartient à un PrivateUser
    // Contrat : aucun

    string getOwnerId ( ) const;
    // Mode d'emploi : Retourne l'ID du propriétaire du sensor
    // Contrat : aucun

    void setIsReliable ( bool isReliable );
    // Mode d'emploi : Définit si le sensor est fiable
    // Contrat : aucun

    string getSensorId ( ) const;
    // Mode d'emploi : Retourne l'ID du sensor
    // Contrat : aucun

    double getLatitude ( ) const;
    // Mode d'emploi : Retourne la latitude
    // Contrat : aucun

    double getLongitude ( ) const;
    // Mode d'emploi : Retourne la longitude
    // Contrat : aucun

    bool getIsReliable ( ) const;
    // Mode d'emploi : Retourne si le sensor est fiable
    // Contrat : aucun

//------------------------------------------------- Surcharge d'opérateurs
    Sensor & operator = ( const Sensor & unCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Sensor ( const Sensor & unCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Sensor ( string sensorId, double latitude, double longitude );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string sensorId;
string ownerId;  
double latitude;
double longitude;
bool isReliable;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // SENSOR_H

