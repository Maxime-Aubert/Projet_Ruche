#include <unistd.h>
#include "BME280.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    char adresse = 0x77;    // Adresse du BME280
    BME280 capteur(adresse);
    
    while(1){
        system("clear");

    cout << "Capteur BME 280" << endl;
    cout << " Température (C) : " << fixed << setprecision (2) << capteur.lireTemperature_DegreCelsius() << " °C"<< endl;
    cout << " Température (F) : " << fixed << setprecision (2) << capteur.lireTemperature_Fahrenheit() << " °F"<< endl;
    cout << " Pression        : " << fixed << setprecision (2) << capteur.lirePression() << " hPa"<< endl;
    cout << " Humidité        : " << fixed << setprecision (2) << capteur.lireHumidite() << " %"<< endl;
    sleep(2);
    }
    return 0;
}
