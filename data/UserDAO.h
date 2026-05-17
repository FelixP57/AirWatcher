//---------- Interface de la classe <UserDAO> (fichier UserDAO.h) ----------------
#if ! defined ( USERDAO_H )
#define USERDAO_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "../model/User.h"
#include "../model/Role.h"
#include "../model/PrivateUser.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <UserDAO>
//
//
//------------------------------------------------------------------------

class UserDAO 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void loadUsersFromCSV(string filename);

    User* authenticate(string login, string password);

    User* getUserById(string userId);

    void addUser(User* user);

    void updatePoints(string userId, int points);

    void blockUser(string userId);

//-------------------------------------------- Constructeurs - destructeur
    UserDAO ( const UserDAO & unUserDAO );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    UserDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~UserDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map<string, User*> users;

};

//-------------------------------- Autres définitions dépendantes de <UserDAO>

#endif // USERDAO_H