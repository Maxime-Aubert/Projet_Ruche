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



using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {

    Driver* driver;
    Connection* connection;
    Statement *stmt;
    INA219 capteur(0x40);

try
{
    driver = get_driver_instance();
    
    //connection = driver -> connect("172.18.58.89", "ruche", "Touchard72");
    //connection = driver -> connect("127.0.0.1:3306", "root", "toto");
    connection = driver->connect( DBHOSTDIST, USERDIST, PASSWORDDIST);
}
catch (sql::SQLException e)
    {   
       cout << "Erreur lors de connection sur la base de donnée distante, renvoie des données sur la base de donnée locale. Message : " << e.what() << endl;
       //exit(1);
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
    sql << "INSERT INTO mesures(ruches_idRuches, tension, courant ) VALUES (" 
            << 1 << "," <<  fixed << setprecision(3) << capteur.lireTension_V() << "," 
            << fixed << setprecision(3) << capteur.lireCourant_A() << ")";
    cout << endl << sql.str() << endl;
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}