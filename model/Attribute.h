/*************************************************************************
                           Attribute  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Attribute> (fichier Attribute.h) ----------------
#if ! defined ( ATTRIBUTE_H )
#define ATTRIBUTE_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <string>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Attribute>
//
//
//------------------------------------------------------------------------

class Attribute 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    int computeAtmoIndex ( double value );
    // Mode d'emploi : Calcule l'indice atmosphérique partir de la valeur
    // Contrat : aucun

    string getAttributeId ( ) const;
    // Mode d'emploi : Retourne l'ID de l'attribut
    // Contrat : aucun

    string getUnit ( ) const;
    // Mode d'emploi : Retourne l'unité de mesure
    // Contrat : aucun

    string getDescription ( ) const;
    // Mode d'emploi : Retourne la description
    // Contrat : aucun

//------------------------------------------------- Surcharge d'opérateurs
    Attribute & operator = ( const Attribute & unCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Attribute ( const Attribute & unCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Attribute ( string attributeId, string unit, string description );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Attribute ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
string attributeId;
string unit;
string description;

};

//-------------------------------- Autres définitions dépendantes de <Attribute>

#endif // ATTRIBUTE_H

