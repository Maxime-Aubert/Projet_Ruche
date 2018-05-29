/*!
    \file     main.cpp
    \author   Maxime Aubert (Touchard Wahington le Mans)
    \license  BSD (see license.txt)
    \date     25 mai 2018
    \brief    Programme test du capteur d'éclairement lumineux bh170
    \details
	compilation : g++ testBH1750.cpp I2C.cpp  BH1750.cpp -o testBH1750
    \version V1.0 First release
*/


#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "BH1750.h"

using namespace std;

int main()
{
    system("clear");
    BH1750 capteur;

    cout << "Capteur d'éclairement" << endl;

    capteur.activer();
    capteur.reset();


    while(1){
        capteur.configurer(BH1750_CONTINUOUS_HIGH_RES_MODE_2);
	cout << "Eclairement : " << fixed << setprecision (1) << capteur.lireEclairement_Lux()  << " lx" << endl;
        sleep(1);

    }
    return 0;
}
