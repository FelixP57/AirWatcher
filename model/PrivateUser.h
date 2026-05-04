/*************************************************************************
                           PrivateUser  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <PrivateUser> (fichier PrivateUser.h) ----------------
#if ! defined ( PRIVATEUSER_H )
#define PRIVATEUSER_H

//--------------------------------------------------- Interfaces utilisées
#include "User.h"
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateUser>
//
//
//------------------------------------------------------------------------

class PrivateUser : public User
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void addPoints(int pointsToAdd);
    // Mode d'emploi : Ajoute des points à l'utilisateur
    // Contrat : aucun

    void blockPointAccumulation();
    // Mode d'emploi : Bloque l'accumulation de points
    // Contrat : aucun

    string getSensorId ( ) const;
    // Mode d'emploi : Retourne l'ID du sensor associé
    // Contrat : aucun

    int getPoints ( ) const;
    // Mode d'emploi : Retourne le nombre de points
    // Contrat : aucun

    bool getIsBlocked ( ) const;
    // Mode d'emploi : Retourne si l'accumulation est bloquée
    // Contrat : aucun

//------------------------------------------------- Surcharge d'opérateurs
    PrivateUser & operator = ( const PrivateUser & unPrivateUser );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    PrivateUser ( const PrivateUser & unPrivateUser );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    PrivateUser ( string userId, string sensorId, string login, string hashedPassword, Role role );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~PrivateUser ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string sensorId;
int points;
bool isBlocked;
};

//-------------------------------- Autres définitions dépendantes de <PrivateUser>

#endif // PRIVATEUSER_H

