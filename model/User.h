/*************************************************************************
                           User  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <User> (fichier User.h) ----------------
#if ! defined ( USER_H )
#define USER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "Role.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <User>
//
//
//------------------------------------------------------------------------

class User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    string getUserId ( ) const;
    // Mode d'emploi : Retourne l'ID de l'utilisateur
    // Contrat : aucun

    string getLogin ( ) const;
    // Mode d'emploi : Retourne le login
    // Contrat : aucun

    string getHashedPassword ( ) const;
    // Mode d'emploi : Retourne le mot de passe hashé
    // Contrat : aucun

    Role getRole ( ) const;
    // Mode d'emploi : Retourne le rôle de l'utilisateur
    // Contrat : aucun

//------------------------------------------------- Surcharge d'opérateurs
    User & operator = ( const User & unUser );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    User ( const User & unUser );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    User ( string userId, string login, string hashedPassword, Role role );
    // Mode d'emploi :
    //
    // Contrat :
    //

    User ( );

    virtual ~User ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string userId;
string login;
string hashedPassword;
Role role;

};

//-------------------------------- Autres définitions dépendantes de <User>

#endif // USER_H

