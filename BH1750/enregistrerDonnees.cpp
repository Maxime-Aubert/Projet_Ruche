/*
 \detail    Prérequis    : sudo apt-get install libmysqlcppconn-dev
            Compilation  : g++ enregistrerDonnees.cpp I2C.cpp  BH1750.cpp -lmysqlcppconn -o enregistrerDonnees
            Execution    : ./enregisterDonnees
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include "BH1750.h"
#define IDRUCHE "1"



using namespace std;
using namespace sql;

int main(int argc, char* argv[]) {

    Driver* driver;
    Connection* connection;
    Statement *stmt;
    BH1750 capteur(0x23);

    driver = get_driver_instance();
    
        
    connection = driver -> connect("172.18.58.89", "ruche", "Touchard72");

    stmt = connection->createStatement();

    // selectionne la base de donnees ruche
    stmt->execute("USE ruche");

    // insertion d'une mesure d'éclairement dans la table mesures
    ostringstream sql;
    sql << "INSERT INTO mesures(ruches_idRuches, eclairementval ) VALUES (" 
    << fixed << setprecision(2) << capteur.lireEclairement_Lux()<< ","
    << IDRUCHE << ")";
    cout << endl << sql.str() << endl;
    stmt->execute(sql.str());

    delete stmt;

    connection -> close();
    delete connection;
    cout << "Done bye" << endl;
    return 0;
}
 
