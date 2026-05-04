/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Measurement> (fichier Measurement.h) ----------------
#if ! defined ( MEASUREMENT_H )
#define MEASUREMENT_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Measurement>
//
//
//------------------------------------------------------------------------

class Measurement 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getTimestamp ( ) const;
    // Mode d'emploi : Retourne le timestamp
    // Contrat : aucun

    string getSensorId ( ) const;
    // Mode d'emploi : Retourne l'ID du sensor
    // Contrat : aucun

    string getAttributeId ( ) const;
    // Mode d'emploi : Retourne l'ID de l'attribut
    // Contrat : aucun

    double getValue ( ) const;
    // Mode d'emploi : Retourne la valeur mesurée
    // Contrat : aucun

    bool getIsValid ( ) const;
    // Mode d'emploi : Retourne si la mesure est valide
    // Contrat : aucun

//------------------------------------------------- Surcharge d'opérateurs
    Measurement & operator = ( const Measurement & unMeasurement );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Measurement ( const Measurement & unMeasurement );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Measurement ( string timestamp, string sensorId, string attributeId, double value, bool isValid );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Measurement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string timestamp;
string sensorId;
string attributeId;
double value;
bool isValid;

};

//-------------------------------- Autres définitions dépendantes de <Measurement>

#endif // MEASUREMENT_H

