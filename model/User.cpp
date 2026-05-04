/*************************************************************************
                           User  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <User> (fichier User.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "User.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string User::getUserId ( ) const
// Algorithme :
//
{
    return userId;
} //----- Fin de getUserId


string User::getLogin ( ) const
// Algorithme :
//
{
    return login;
} //----- Fin de getLogin


string User::getHashedPassword ( ) const
// Algorithme :
//
{
    return hashedPassword;
} //----- Fin de getHashedPassword


Role User::getRole ( ) const
// Algorithme :
//
{
    return role;
} //----- Fin de getRole


//------------------------------------------------- Surcharge d'opérateurs
User & User::operator = ( const User & unUser )
// Algorithme :
//
{
    this->userId = unUser.userId;
    this->login = unUser.login;
    this->hashedPassword = unUser.hashedPassword;
    this->role = unUser.role;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
User::User ( const User & unUser )
// Algorithme :
//
{
    this->userId = unUser.userId;
    this->login = unUser.login;
    this->hashedPassword = unUser.hashedPassword;
    this->role = unUser.role;
#ifdef MAP
    cout << "Appel au constructeur de copie de <User>" << endl;
#endif
} //----- Fin de User (constructeur de copie)


User::User ( string userId, string login, string hashedPassword, Role role )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <User>" << endl;
#endif
    this->userId = userId;
    this->login = login;
    this->hashedPassword = hashedPassword;
    this->role = role;
} //----- Fin de User

User::User ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <User>" << endl;
#endif
} //----- Fin de User (constructeur par défaut)


User::~User ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <User>" << endl;
#endif
} //----- Fin de ~User


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

