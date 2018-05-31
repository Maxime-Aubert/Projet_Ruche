#include "BH1750.h"
#include "I2C.h"

using namespace std;


// Constructeur
BH1750::BH1750(int addressBH1750)
{
    deviceI2C = new I2C(addressBH1750);
    resolution = 1.0;

}


// Destructeur
BH1750::~BH1750()
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}


// Méthode pour obtenir la valeur de l'éclairement en lx
float BH1750::lireEclairement_Lux()
{
    unsigned short level;
    level = deviceI2C->I2CReadReg16(0x00);
    level = ((level & 0x00FF) << 8) | ((level & 0xFF00) >> 8); // inversion msb lsb
    // Convert raw value to lux and return
    if (resolution == 1.0){
    	return (float)level / 1.2;
    }
    else{
	return (float)level * resolution / 1.2 ;
    }
}


// Méthode pour configuer le mode de fct :

void BH1750::activer(void)
{
    deviceI2C->I2CWrite(BH1750_POWER_ON);
}

void BH1750::desactiver(void)
{
    deviceI2C->I2CWrite(BH1750_POWER_DOWN);
}

void BH1750::reset(void)
{
    deviceI2C->I2CWrite( BH1750_RESET);
}

void BH1750::configurer(int mode)
{
    switch (mode)
    {
        case BH1750_CONTINUOUS_HIGH_RES_MODE:
        case BH1750_CONTINUOUS_LOW_RES_MODE:
        case BH1750_ONE_TIME_HIGH_RES_MODE:
        case BH1750_ONE_TIME_LOW_RES_MODE:
            
            deviceI2C->I2CWrite(mode);
            resolution = 1.0;
            deviceI2C->delay_ms(180);
            break;

        case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
        case BH1750_ONE_TIME_HIGH_RES_MODE_2:
            
            deviceI2C->I2CWrite(mode);
            resolution = 0.5;
            deviceI2C->delay_ms(180);
            break;

        default:
            // // Mode de mesure invalide
            printf("// Mode de mesure invalide !\n");
            break;
    }
}
