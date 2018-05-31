/*
 \detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
            Compilation  : g++ synchronisation.cpp -lmysqlcppconn -o synchronisation
            Execution    : ./synchronisation
            Pour executer périodiquement toutes les heures ajouter avec crontab
		    en tant que super utilisateur (sudo crontab -e)
*/


#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/driver.h>

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#define DBHOSTDIST "tcp://172.18.58.89:3306/ruche"
#define USERDIST "ruche"
#define PASSWORDDIST "Touchard72"
#define USERLOC "local"
#define DBHOSTLOC "tcp://127.0.0.1:3306/ruche"
#define PASSWORDLOC "toto"

using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {

    Driver* driver;           // Pour établir une connexion au serveur MySQL
    Connection* conLocale;    // Pour établir une connexion au serveur MySQL de la base de données locale
    Connection* conDistante;  // Pour établir une connexion au serveur MySQL de la base de données distante
    Statement * stmtLocale;   // Pour exécuter des requêtes simples sur la base de données locale
    Statement * stmtDistante; // Pour exécuter des requêtes simples sur la base de données distante
    ResultSet*  resLocale;    // Objet contenant le résultat de la requete de la base de données locale
    ResultSet*  resDistante;  // Objet contenant le résultat de la requete de la base de données distante

    double eclairementval, pressionval, tempval, poidsval, humidval;
    double tempfahr, tension, courant;
    string date;
    int ruches_idRuches;
    ostringstream sql;

    // La gestion d'erreur se fait avec les exceptions (try catch)
    try
    {
        // Création d'une connexion à la base de données distante et locale
        driver = get_driver_instance();
        conDistante = driver->connect( DBHOSTDIST, USERDIST, PASSWORDDIST);
        conLocale = driver->connect(DBHOSTLOC, USERLOC, PASSWORDLOC);

    }
    catch (sql::SQLException e)
    {
       cout << "Erreur lors des connections sur les serveurs, Message : " << e.what() << endl;
       exit(1);
    }
    
    // Création d'un objet qui permet d'effectuer des requêtes sur la base de données locale
    stmtLocale = conLocale->createStatement();

    // Exécution d'une requete SELECT : ici on sélectionne tous les enregistrements
    // de la table mesures
    resLocale = stmtLocale->executeQuery("SELECT * FROM mesures");

    // Création d'un objet qui permet d'effectuer des requêtes sur la base de données distante
    stmtDistante = conDistante->createStatement();

    // Exploitation du résultat de la requête
    while(resLocale->next()) {
       eclairementval=resLocale->getDouble(2);
       pressionval=resLocale->getDouble(3);
       tempval=resLocale->getDouble(4); 
       poidsval=resLocale->getDouble(5);
       humidval=resLocale->getDouble(6);
       tempfahr=resLocale->getDouble(7);
       tension=resLocale->getDouble(8);
       courant=resLocale->getDouble(9);
       date=resLocale->getString(10);
       ruches_idRuches=resLocale->getInt(11);
        
       // Vide le flux
       sql.str("");

       // Efface les défauts
       sql.clear();
    
       // Insertion des valeurs
       // d'éclairement en lux,
       // de pression en hPa,
       // de température en Celsius,
       // de poids en g,
       // d'humidité relative en %,
       // de température en Fahrenheit,
       // de tension en Volt,
       // de courant en Ampere,
       // de date,
       // et d'identifiant de la ruche
       // dans la table mesures de la base se données ruche
       sql << "INSERT INTO mesures(eclairementval, pressionval, tempval, poidsval, humidval, tempfahr, tension, courant, date, ruches_idRuches) VALUES (" 
            << fixed << setprecision(2) << eclairementval << ","
            << fixed << setprecision(2) << pressionval << ","
            << fixed << setprecision(2) << tempval << ","
            << fixed << setprecision(2) << poidsval << ","
            << fixed << setprecision(2) << humidval << ","
            << fixed << setprecision(2) << tempfahr << ","
            << fixed << setprecision(3) << tension << ","
            << fixed << setprecision(3) << courant << " , '"
            << date << "' ,"
            << ruches_idRuches << ")";

       // Affichage pour contrôle
       cout << endl << sql.str() << endl;
       
       // Exécution de la requete
       stmtDistante->execute(sql.str());


    }
    
    // Exécution d'une requete DELETE : ici on supprime tous les enregistrements
    // de la table mesures
    stmtLocale->execute("DELETE FROM `mesures`");
    
    // Libération de la mémoire avant de quitter
    delete stmtDistante;
    delete stmtLocale;
    delete conLocale;
    delete conDistante;
    delete resLocale;
    delete resDistante;

    cout << "Done bye" << endl;

    return 0;
    
 
}
