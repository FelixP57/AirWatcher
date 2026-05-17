/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Sensor::isPrivate ( )
// Algorithme : Vérifie si le sensor appartient à un PrivateUser
// Le sensor est privé si ownerId n'est pas vide
{
    return !ownerId.empty();
} //----- Fin de isPrivate


string Sensor::getOwnerId ( ) const
// Algorithme :
//
{
    return ownerId;
} //----- Fin de getOwnerId


void Sensor::setIsReliable ( bool isReliable )
// Algorithme :
//
{
    this->isReliable = isReliable;
} //----- Fin de setIsReliable


string Sensor::getSensorId ( ) const
// Algorithme :
//
{
    return sensorId;
} //----- Fin de getSensorId


double Sensor::getLatitude ( ) const
// Algorithme :
//
{
    return latitude;
} //----- Fin de getLatitude


double Sensor::getLongitude ( ) const
// Algorithme :
//
{
    return longitude;
} //----- Fin de getLongitude


bool Sensor::getIsReliable ( ) const
// Algorithme :
//
{
    return isReliable;
} //----- Fin de getIsReliable


//------------------------------------------------- Surcharge d'opérateurs
Sensor & Sensor::operator = ( const Sensor & unSensor )
// Algorithme :
//
{
    this->sensorId = unSensor.sensorId;
    this->ownerId = unSensor.ownerId;
    this->latitude = unSensor.latitude;
    this->longitude = unSensor.longitude;
    this->isReliable = unSensor.isReliable;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor ( const Sensor & unSensor )
// Algorithme :
//
{
    this->sensorId = unSensor.sensorId;
    this->ownerId = unSensor.ownerId;
    this->latitude = unSensor.latitude;
    this->longitude = unSensor.longitude;
    this->isReliable = unSensor.isReliable;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Sensor>" << endl;
#endif
} //----- Fin de Sensor (constructeur de copie)


Sensor::Sensor ( string sensorId, double latitude, double longitude ) : sensorId(sensorId), ownerId(""), latitude(latitude), longitude(longitude), isReliable(true)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
} //----- Fin de Sensor


Sensor::~Sensor ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

