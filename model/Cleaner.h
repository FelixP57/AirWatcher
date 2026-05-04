/*************************************************************************
                           Cleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Cleaner> (fichier Cleaner.h) ----------------
#if ! defined ( CLEANER_H )
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
//
//
//------------------------------------------------------------------------

class Cleaner 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getCleanerId ( ) const;
    // Mode d'emploi : Retourne l'ID du cleaner
    // Contrat : aucun

    double getLatitude ( ) const;
    // Mode d'emploi : Retourne la latitude
    // Contrat : aucun

    double getLongitude ( ) const;
    // Mode d'emploi : Retourne la longitude
    // Contrat : aucun

    string getTimestampStart ( ) const;
    // Mode d'emploi : Retourne le timestamp de début
    // Contrat : aucun

    string getTimestampStop ( ) const;
    // Mode d'emploi : Retourne le timestamp de fin
    // Contrat : aucun

    string getProviderId ( ) const;
    // Mode d'emploi : Retourne l'ID du provider
    // Contrat : aucun

//------------------------------------------------- Surcharge d'opérateurs
    Cleaner & operator = ( const Cleaner & unCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Cleaner ( const Cleaner & unCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Cleaner ( string cleanerId, double latitude, double longitude, string timestampStart, string timestampStop, string providerId );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Cleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string cleanerId;
double latitude;
double longitude;
string timestampStart;
string timestampStop;
string providerId;

};

//-------------------------------- Autres définitions dépendantes de <Cleaner>

#endif // CLEANER_H

