//---------- Interface de la classe <CleanerDAO> (fichier CleanerDAO.h) ----------------
#if ! defined ( CLEANERDAO_H )
#define CLEANERDAO_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

#include "../model/Cleaner.h"
#include "../model/Provider.h"
#include "../model/Role.h"

using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <CleanerDAO>
//
//
//------------------------------------------------------------------------

class CleanerDAO 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void loadCleanersFromCSV(string filename);

    void loadProvidersFromCSV(string filename);

    Cleaner* getCleanerById(string cleanerId);

    vector<Cleaner> getNearByCleaners(double longitude, double latitude, double radius);

    double computeDistance(double lon1, double lat1, double lon2, double lat2);

//-------------------------------------------- Constructeurs - destructeur
    CleanerDAO ( const CleanerDAO & unCleanerDAO );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    CleanerDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~CleanerDAO ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    map<string, Cleaner> cleaners;
    map<string, Provider> providers;

};

//-------------------------------- Autres définitions dépendantes de <CleanerDAO>

#endif // CLEANERDAO_H

