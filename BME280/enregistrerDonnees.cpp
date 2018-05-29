/*
 \detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
            Compilation  : g++ enregistrerDonnees.cpp I2C.cpp  BME280.cpp -lmysqlcppconn -o enregistrerDonnees
            Execution    : ./enregistrerDonnees          
*/

#include <stdlib.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include "mysql_connection.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include "BME280.h"

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
    BME280 capteur(0x77);

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

    // insertion d'une mesure de température en Celsius,
    // de température en Fahrenheit,
    // de pression en hPa,
    // et d'humidité relative en % dans la table mesures
    ostringstream sql;
    sql << "INSERT INTO mesures(pressionval, tempval, humidval, tempfahr, ruches_idRuches ) VALUES (" 
            << fixed << setprecision(2) << capteur.lirePression() << ","
            << fixed << setprecision(2) << capteur.lireTemperature_DegreCelsius() << ","
            << fixed << setprecision(2) << capteur.lireHumidite() << ","
            << fixed << setprecision(2) << capteur.lireTemperature_Fahrenheit() << ","
            << IDRUCHE << ")";
    cout << endl << sql.str() << endl;
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
