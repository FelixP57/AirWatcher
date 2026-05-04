/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Provider> (fichier Provider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<string> Provider::getCleanerIds ( ) const
// Algorithme :
//
{
    return cleanerIds;
} //----- Fin de getCleanerIds


//------------------------------------------------- Surcharge d'opérateurs
Provider & Provider::operator = ( const Provider & unProvider )
// Algorithme :
//
{
    User::operator=(unProvider);
    this->cleanerIds = unProvider.cleanerIds;
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Provider::Provider ( const Provider & unProvider )
// Algorithme :
//
{
    this->userId = unProvider.userId;
    this->login = unProvider.login;
    this->hashedPassword = unProvider.hashedPassword;
    this->role = unProvider.role;
    this->cleanerIds = unProvider.cleanerIds;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Provider>" << endl;
#endif
} //----- Fin de Provider (constructeur de copie)


Provider::Provider ( string userId, string login, string hashedPassword, Role role, const vector<string> & cleanerIds ) : User(userId, login, hashedPassword, role), cleanerIds(cleanerIds)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Provider>" << endl;
#endif
} //----- Fin de Provider


Provider::~Provider ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
