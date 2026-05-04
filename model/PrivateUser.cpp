/*************************************************************************
                           PrivateUser  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <PrivateUser> (fichier PrivateUser.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "PrivateUser.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void PrivateUser::addPoints(int pointsToAdd)
// Algorithme :
//
{
    points += pointsToAdd;
}

void PrivateUser::blockPointAccumulation()
// Algorithme :
//
{
    isBlocked = true;
}

string PrivateUser::getSensorId ( ) const
// Algorithme :
//
{
    return sensorId;
} //----- Fin de getSensorId


int PrivateUser::getPoints ( ) const
// Algorithme :
//
{
    return points;
} //----- Fin de getPoints


bool PrivateUser::getIsBlocked ( ) const
// Algorithme :
//
{
    return isBlocked;
} //----- Fin de getIsBlocked


//------------------------------------------------- Surcharge d'opérateurs
PrivateUser & PrivateUser::operator = ( const PrivateUser & unPrivateUser )
// Algorithme :
//
{
    User::operator=(unPrivateUser);
    this->sensorId = unPrivateUser.sensorId;
    this->points = unPrivateUser.points;
    this->isBlocked = unPrivateUser.isBlocked;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
PrivateUser::PrivateUser ( const PrivateUser & unPrivateUser )
// Algorithme :
//
{
    this->userId = unPrivateUser.userId;
    this->login = unPrivateUser.login;
    this->hashedPassword = unPrivateUser.hashedPassword;
    this->role = unPrivateUser.role;
    this->sensorId = unPrivateUser.sensorId;
    this->points = unPrivateUser.points;
    this->isBlocked = unPrivateUser.isBlocked;
#ifdef MAP
    cout << "Appel au constructeur de copie de <PrivateUser>" << endl;
#endif
} //----- Fin de PrivateUser (constructeur de copie)


PrivateUser::PrivateUser ( string userId, string sensorId, string login, string hashedPassword, Role role )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <PrivateUser>" << endl;
#endif
    this->userId = userId;
    this->sensorId = sensorId;
    this->login = login;
    this->hashedPassword = hashedPassword;
    this->role = role;
    this->points = 0;
    this->isBlocked = false;
} //----- Fin de PrivateUser


PrivateUser::~PrivateUser ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PrivateUser>" << endl;
#endif
} //----- Fin de ~PrivateUser


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

