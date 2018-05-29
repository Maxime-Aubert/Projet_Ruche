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

    Driver* driver;
    Connection* conLocale;
    Connection* conDistante;
    Statement * stmtLocale;
    Statement * stmtDistante;
    ResultSet*  resLocale;
    ResultSet*  resDistante;

    double eclairementval, pressionval, tempval, poidsval, humidval;
    double tempfahr, tension, courant;
    string date;
    int ruches_idRuches;
    ostringstream sql;

    try
    {
        driver = get_driver_instance();
        conDistante = driver->connect( DBHOSTDIST, USERDIST, PASSWORDDIST);
        conLocale = driver->connect(DBHOSTLOC, USERLOC, PASSWORDLOC);

    }
    catch (sql::SQLException e)
    {
       cout << "Erreur lors des connections sur les serveurs, Message : " << e.what() << endl;
       exit(1);
    }
    stmtLocale = conLocale->createStatement();
    resLocale = stmtLocale->executeQuery("SELECT * FROM mesures");

    stmtDistante = conDistante->createStatement();

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

       sql.str("");
       sql.clear();

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

       cout << endl << sql.str() << endl;
       stmtDistante->execute(sql.str());


    }
    //stmtLocale = conLocale->createStatement();
    stmtLocale->execute("DELETE FROM `mesures`");
    
    delete stmtDistante;
    delete stmtLocale;
    delete conLocale;
    delete conDistante;
    cout << "Done bye" << endl;
    return 0;
    
 
}
