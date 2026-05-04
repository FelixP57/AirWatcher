/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Attribute> (fichier Attribute.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Attribute.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Attribute::computeAtmoIndex ( double value )
// Algorithme :
//
{
    int atmoIndex = 0;
    switch (attributeId[0]) {
        case 'o': // ozone
            if (value <= 50) atmoIndex = 1;
            else if (value <= 100) atmoIndex = 2;
            else if (value <= 130) atmoIndex = 3;
            else if (value <= 240) atmoIndex = 4;
            else if (value <= 380) atmoIndex = 5;
            else atmoIndex = 6;
            break;
        case 'n': // NO2
            if (value <= 40) atmoIndex = 1;
            else if (value <= 90) atmoIndex = 2;
            else if (value <= 120) atmoIndex = 3;
            else if (value <= 230) atmoIndex = 4;
            else if (value <= 340) atmoIndex = 5;
            else atmoIndex = 6;
            break;
        case 'p': // PM10
            if (value <= 20) atmoIndex = 1;
            else if (value <= 40) atmoIndex = 2;
            else if (value <= 50) atmoIndex = 3;
            else if (value <= 100) atmoIndex = 4;
            else if (value <= 150) atmoIndex = 5;
            else atmoIndex = 6;
            break;
        case 's': // SO2
            if (value <= 100) atmoIndex = 1;
            else if (value <= 200) atmoIndex = 2;
            else if (value <= 350) atmoIndex = 3;
            else if (value <= 500) atmoIndex = 4;
            else if (value <= 750) atmoIndex = 5;
            else atmoIndex = 6;
            break;
        default:
            cerr << "Unknown attributeId: " << attributeId << endl; // Log an error message
    }
    return atmoIndex;
} //----- Fin de computeAtmoIndex


string Attribute::getAttributeId ( ) const
// Algorithme :
//
{
    return attributeId;
} //----- Fin de getAttributeId


string Attribute::getUnit ( ) const
// Algorithme :
//
{
    return unit;
} //----- Fin de getUnit


string Attribute::getDescription ( ) const
// Algorithme :
//
{
    return description;
} //----- Fin de getDescription


//------------------------------------------------- Surcharge d'opérateurs
Attribute & Attribute::operator = ( const Attribute & unAttribute )
// Algorithme :
//
{
    this->attributeId = unAttribute.attributeId;
    this->unit = unAttribute.unit;
    this->description = unAttribute.description;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Attribute::Attribute ( const Attribute & unAttribute )
// Algorithme :
//
{
    this->attributeId = unAttribute.attributeId;
    this->unit = unAttribute.unit;
    this->description = unAttribute.description;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Attribute>" << endl;
#endif
} //----- Fin de Attribute (constructeur de copie)


Attribute::Attribute ( string attributeId, string unit, string description ) : attributeId(attributeId), unit(unit), description(description)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Attribute>" << endl;
#endif
} //----- Fin de Attribute


Attribute::~Attribute ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Attribute>" << endl;
#endif
} //----- Fin de ~Attribute


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

