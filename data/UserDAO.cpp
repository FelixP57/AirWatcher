/*************************************************************************
                           UserDAO  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <UserDAO> (fichier UserDAO.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "UserDAO.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type UserDAO::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void UserDAO::loadUsersFromCSV(string filename) {
    
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        int data = 0;
        while (!file.eof()) {
            if (file.peek() == EOF) {
                break; // Exit the function if the file is empty
            }

            getline(file, line, ';');
            string userId = line;
            // cout << "User ID: " << userId << endl;

            getline(file, line, ';');
            string sensorId = line;
            // cout << "Sensor ID: " << sensorId << endl;

            getline(file, line, '\n');

            if (data == 0) {
                User* user = new User(userId, userId, "123", Role::USER);
                users.insert(pair<string, User*>(userId, user));
            } else {
                User* user = new User(userId, userId, "", Role::USER);
                users.insert(pair<string, User*>(userId, user));
            }
            
        }
        for (const auto& pair : users) {
            cout <<"User ID: " << pair.first << endl;
        }
    }

    file.close();
}

User* UserDAO::authenticate(string userId, string password) {
    // I assumed that the login and the userId are the same
    if (users.find(userId) != users.end() && users.find(userId)->second->getHashedPassword() == password) {
        return users.find(userId)->second;
    } else {
        return nullptr;
    }
}

User* UserDAO::getUserById(string userId) {
    if (users.find(userId) != users.end()) {
        return users.find(userId)->second;
    } else {
        return nullptr;
    }
}

void UserDAO::addUser(User* user) {
    users.insert(pair<string, User*>(user->getUserId(), user));
}

void UserDAO::updatePoints(string userId, int points) {
    if (users.find(userId) != users.end()) {
        dynamic_cast<PrivateUser*>(users.find(userId)->second)->addPoints(points);
    }
}

void UserDAO::blockUser(string userId) {
    if (users.find(userId) != users.end()) {
        dynamic_cast<PrivateUser*>(users.find(userId)->second)->blockPointAccumulation();
    }
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
UserDAO::UserDAO ( const UserDAO & unUserDAO )
// Algorithme :
//
{
        this->users = unUserDAO.users;
#ifdef MAP
    cout << "Appel au constructeur de copie de <UserDAO>" << endl;
#endif
} //----- Fin de UserDAO (constructeur de copie)


UserDAO::UserDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UserDAO>" << endl;
#endif
} //----- Fin de UserDAO


UserDAO::~UserDAO ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UserDAO>" << endl;
#endif
} //----- Fin de ~UserDAO

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées