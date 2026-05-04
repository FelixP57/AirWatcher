/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Cleaner> (fichier Cleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string Cleaner::getCleanerId ( ) const
// Algorithme :
//
{
    return cleanerId;
} //----- Fin de getCleanerId


double Cleaner::getLatitude ( ) const
// Algorithme :
//
{
    return latitude;
} //----- Fin de getLatitude


double Cleaner::getLongitude ( ) const
// Algorithme :
//
{
    return longitude;
} //----- Fin de getLongitude


string Cleaner::getTimestampStart ( ) const
// Algorithme :
//
{
    return timestampStart;
} //----- Fin de getTimestampStart


string Cleaner::getTimestampStop ( ) const
// Algorithme :
//
{
    return timestampStop;
} //----- Fin de getTimestampStop


string Cleaner::getProviderId ( ) const
// Algorithme :
//
{
    return providerId;
} //----- Fin de getProviderId


//------------------------------------------------- Surcharge d'opérateurs
Cleaner & Cleaner::operator = ( const Cleaner & unCleaner )
// Algorithme :
//
{
    this->cleanerId = unCleaner.cleanerId;
    this->latitude = unCleaner.latitude;
    this->longitude = unCleaner.longitude;
    this->timestampStart = unCleaner.timestampStart;
    this->timestampStop = unCleaner.timestampStop;
    this->providerId = unCleaner.providerId;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner ( const Cleaner & unCleaner )
// Algorithme :
//
{
    this->cleanerId = unCleaner.cleanerId;
    this->latitude = unCleaner.latitude;
    this->longitude = unCleaner.longitude;
    this->timestampStart = unCleaner.timestampStart;
    this->timestampStop = unCleaner.timestampStop;
    this->providerId = unCleaner.providerId;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner (constructeur de copie)


Cleaner::Cleaner ( string cleanerId, double latitude, double longitude, string timestampStart, string timestampStop, string providerId )
 : cleanerId(cleanerId), latitude(latitude), longitude(longitude), timestampStart(timestampStart), timestampStop(timestampStop), providerId(providerId)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner


Cleaner::~Cleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

