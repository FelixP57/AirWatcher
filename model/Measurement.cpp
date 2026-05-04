/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Measurement> (fichier Measurement.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Measurement::getTimestamp ( ) const
// Algorithme :
//
{
    return timestamp;
} //----- Fin de getTimestamp


string Measurement::getSensorId ( ) const
// Algorithme :
//
{
    return sensorId;
} //----- Fin de getSensorId


string Measurement::getAttributeId ( ) const
// Algorithme :
//
{
    return attributeId;
} //----- Fin de getAttributeId


double Measurement::getValue ( ) const
// Algorithme :
//
{
    return value;
} //----- Fin de getValue


bool Measurement::getIsValid ( ) const
// Algorithme :
//
{
    return isValid;
} //----- Fin de getIsValid


//------------------------------------------------- Surcharge d'opérateurs
Measurement & Measurement::operator = ( const Measurement & unMeasurement )
// Algorithme :
//
{
    this->timestamp = unMeasurement.timestamp;
    this->sensorId = unMeasurement.sensorId;
    this->attributeId = unMeasurement.attributeId;
    this->value = unMeasurement.value;
    this->isValid = unMeasurement.isValid;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement ( const Measurement & unMeasurement )
// Algorithme :
//
{
    this->timestamp = unMeasurement.timestamp;
    this->sensorId = unMeasurement.sensorId;
    this->attributeId = unMeasurement.attributeId;
    this->value = unMeasurement.value;
    this->isValid = unMeasurement.isValid;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Measurement>" << endl;
#endif
} //----- Fin de Measurement (constructeur de copie)


Measurement::Measurement ( string timestamp, string sensorId, string attributeId, double value, bool isValid )
 : timestamp(timestamp), sensorId(sensorId), attributeId(attributeId), value(value), isValid(isValid)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Measurement>" << endl;
#endif
} //----- Fin de Measurement


Measurement::~Measurement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
#endif
} //----- Fin de ~Measurement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

