/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if ! defined ( PROVIDER_H )
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <vector>
#include <string>
#include "User.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Provider>
//
//
//------------------------------------------------------------------------

class Provider : User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    vector<string> getCleanerIds ( ) const;
    // Mode d'emploi : Retourne la liste des IDs des cleaners
    // Contrat : aucun

    void setCleanerIds ( const vector<string> & cleanerIds );
    // Mode d'emploi : Définit la liste des IDs des cleaners
    // Contrat : aucun 

//------------------------------------------------- Surcharge d'opérateurs
    Provider & operator = ( const Provider & unProvider );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Provider ( const Provider & unProvider );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Provider ( string userId, string login, string hashedPassword, Role role, const vector<string> & cleanerIds );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Provider ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
vector<string> cleanerIds;

};

//-------------------------------- Autres définitions dépendantes de <Provider>

#endif // PROVIDER_H
