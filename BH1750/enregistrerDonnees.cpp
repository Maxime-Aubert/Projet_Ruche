/*
 \detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
            Compilation  : g++ enregistrerDonnees.cpp I2C.cpp  BH1750.cpp -lmysqlcppconn -o enregistrerDonnees
            Execution    : ./enregisterDonnees
            Pour executer périodiquement toutes les 10 minutes ajouter avec crontab
		    en tant que super utilisateur (sudo crontab -e)
 
 */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include "BH1750.h"

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

    Driver* driver;
    Connection* connection;
    Statement *stmt;
    BH1750 capteur(0x23);

    try
{
    driver = get_driver_instance();
    connection = driver->connect( DBHOSTDIST, USERDIST, PASSWORDDIST);
}
catch (sql::SQLException e)
    {   
       cout << "Erreur lors de connection sur la base de donnée distante, renvoie des données sur la base de donnée locale. Message : " << e.what() << endl;
    
    try
    {
        driver = get_driver_instance();
        connection = driver->connect( DBHOSTLOC, USERLOC, PASSWORDLOC);
        
    }
   catch (sql::SQLException e)
    {   
       cout << "Erreur lors de la connection. Message : " << e.what() << endl;
       exit(1);
    } 
       
}

    stmt = connection->createStatement();

    // selectionne la base de donnees ruche
    stmt->execute("USE ruche");

    // insertion d'une mesure de température en Celsius, de température en Fahrenheit, de pression, et d'humidité dans la table mesures
    ostringstream sql;
    sql << "INSERT INTO mesures(eclairementval, ruches_idRuches ) VALUES (" 
    <<  fixed << setprecision(2) << capteur.lireEclairement_Lux() << ","
    << IDRUCHE << ")"; 
    
    cout << endl << sql.str() << endl;
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
 
