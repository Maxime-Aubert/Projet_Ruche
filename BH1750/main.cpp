/*
 \details compilation : g++ main.cpp I2C.cpp  BH1750.cpp -o main
 */

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "BH1750.h"

using namespace std;

int main()
{
    
    BH1750 capteur;

    cout << "Capteur d'éclairement" << endl;

    capteur.activer();
    capteur.reset();


    while(1){
        system("clear");
        capteur.configurer(BH1750_CONTINUOUS_HIGH_RES_MODE_2);
	cout << "Eclairement : " << fixed << setprecision (2) << capteur.lireEclairement_Lux()  << " lx" << endl;
        sleep(2);
        

    }
    return 0;
}