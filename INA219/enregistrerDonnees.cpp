/*
 \detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
            Compilation  : g++ enregistrerDonnees.cpp I2C.cpp  INA219.cpp -lmysqlcppconn -o enregistrerDonnees
            Execution    : ./enregistrerDonnees
            Pour executer périodiquement toutes les 10 minutes ajouter avec crontab
		    en tant que super utilisateur (sudo crontab -e)
*/

#include <stdlib.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include "mysql_connection.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cppconn/driver.h>
//#include <cppconn/connection.h>
//#include <cppconn/statement.h>
#include "INA219.h"

#define DBHOSTDIST "tcp://172.18.58.89:3306/ruche"
#define USERDIST "ruche"
#define PASSWORDDIST "Touchard72"
#define USERLOC "root"
#define DBHOSTLOC "tcp://127.0.0.1:3306/ruche"
#define PASSWORDLOC "toto"
#define IDRUCHE "1"



using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {

    Driver* driver;         // Pour établir une connexion au serveur MySQL
    Connection* connection; // Pour établir une connexion au serveur MySQL
    Statement *stmt;        // Pour exécuter des requêtes simples
    INA219 capteur(0x40);   // Déclaration du capteur INA219 à l'adresse par défaut 0x40

// La gestion d'erreur se fait avec les exceptions (try catch)
try
{
    // Création d'une connexion à la base de données distante
    driver = get_driver_instance();
    connection = driver->connect( DBHOSTDIST, USERDIST, PASSWORDDIST);
}
catch (sql::SQLException e)
    {   
       cout << "Erreur lors de connection sur la base de donnée distante, renvoie des données sur la base de donnée locale. Message : " << e.what() << endl;
       //exit(1);
    try
    {
        // Création d'une connexion à la base de données locale
        driver = get_driver_instance();
        connection = driver->connect( DBHOSTLOC, USERLOC, PASSWORDLOC);
        
    }
   catch (sql::SQLException e)
    {   
       cout << "Erreur lors de la connection. Message : " << e.what() << endl;
       exit(1);
   } 
       
    }

    // Création d'un objet qui permet d'effectuer des requêtes sur la base de données
    stmt = connection->createStatement();

    // Selectionne la base de donnees ruche
    stmt->execute("USE ruche");

    // Insertion d'une mesure de tension en Volt,
    // de courant en Ampere
    // et le numéro d'identifiant de la ruche dans la table mesures
    ostringstream sql;
    sql << "INSERT INTO mesures(tension, courant, ruches_idRuches ) VALUES (" 
            <<  fixed << setprecision(3) << capteur.lireTension_V() << ","
            << fixed << setprecision(3) << capteur.lireCourant_A() << ","
            << IDRUCHE << ")";
    
    cout << endl << sql.str() << endl;
    stmt->execute(sql.str());

    // Libération de la mémoire avant de quitter
    delete stmt;

    connection -> close();
    delete connection;

    cout << "Done bye" << endl;

    return 0;
}
