#include <unistd.h>
#include "BME280.h"
#include "BH1750.h"
#include <iostream>
#include <iomanip>

using namespace std;


int main()
{
    BME280 capteurBME(0x77);
    BH1750 capteurBH(0x23);
    
    capteurBH.activer();
    capteurBH.reset();
    
    while(1){
        system("clear");

    cout << "Capteur BME 280 et BH1750" << endl;

   
    capteurBH.configurer(BH1750_CONTINUOUS_HIGH_RES_MODE_2);

    cout << " Température (C) : " << fixed << setprecision (2) << capteurBME.lireTemperature_DegreCelsius() << " °C"<< endl;
    cout << " Température (F) : " << fixed << setprecision (2) << capteurBME.lireTemperature_Fahrenheit() << " °F"<< endl;
    cout << " Pression        : " << fixed << setprecision (2) << capteurBME.lirePression() << " hPa"<< endl;
    cout << " Humidité        : " << fixed << setprecision (2) << capteurBME.lireHumidite() << " %"<< endl;
    cout << " Eclairement     : " << fixed << setprecision (2) << capteurBH.lireEclairement_Lux()  << " lx" << endl;
    sleep(2);
    }
    return 0;
}
