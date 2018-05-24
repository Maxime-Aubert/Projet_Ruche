/*
 \details compilation : g++ main.cpp I2C.cpp INA219.cpp -o main
 */

#include <iostream>
#include <unistd.h>
#include "INA219.h"

using namespace std;

int main()
{
    system("clear");
    char adresse = 0x40;
    INA219 capteur(adresse);

    float en = 0.0; // l'energie en J (Ws)
    int t = 2;  // période d'échantillonage (2s)

    capteur.fixerCalibration_16V();

    cout << "Capteur INA219" << endl;
    while(1){

        cout << " Tension bus   : " << fixed << setprecision (3) << capteur.lireTension_V()  << " V" << endl;
        cout << " Tension shunt : " << fixed << setprecision (3) << capteur.lireTensionShunt_mV() << " mV" << endl;
        cout << " Courant bus   : " << fixed << setprecision (3) << capteur.lireCourant_A() << " A" << endl;
        cout << " Puissance bus : " << fixed << setprecision (3) << capteur.lirePuissance_W() << " W" << endl;
        cout << " Batterie SOC  : " << fixed << setprecision (0) << capteur.lireBatterieSOC() << " %" << endl;
	en += capteur.lirePuissance_W() * t;
	cout << " Energie       : " << fixed << setprecision (3) << en / 3.6 << " mWh" << endl;
	sleep(t);
        system("clear");
    }


    return 0;
}
