#include "BH1750.h"
#include "I2C.h"

using namespace std;


BH1750::~BH1750()
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}

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


//Methode pour configuer le mode de fct
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
            // apply mode 1 res 1 lx
            deviceI2C->I2CWrite(mode);
            resolution = 1.0;
            deviceI2C->delay_ms(180);
            break;

        case BH1750_CONTINUOUS_HIGH_RES_MODE_2:
        case BH1750_ONE_TIME_HIGH_RES_MODE_2:
            // apply mode 2 res 0.5 lx
            deviceI2C->I2CWrite(mode);
            resolution = 0.5;
            deviceI2C->delay_ms(180);
            break;

        default:
            // Invalid measurement mode
            printf("Invalid measurement mode !\n");
            break;
    }
}
