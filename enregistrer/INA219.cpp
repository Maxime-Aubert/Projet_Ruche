#include "INA219.h"
#include "I2C.h"


// Constructeur
INA219::INA219(int addressINA219, float  _quantum)
{
    deviceI2C = new I2C(addressINA219);
    if (!deviceI2C->getError()){
    	deviceI2C->I2CWriteReg16(INA219_REG_CONFIG, 0x0080);   // reset

    	short rc = 4096;
    	rc = ((rc & 0x00FF) << 8) | ((rc & 0xFF00) >> 8);
    	deviceI2C->I2CWriteReg16(INA219_REG_CALIBRATION , rc);  // écriture du registre de calibration

    	uint16_t config;
    	config  = BVOLTAGERANGE_32V | INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_SADCRES_12BIT_128S_69MS | INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
    	config = ((config & 0x00FF) << 8) | ((config & 0xFF00) >> 8);  // inversion msb lsb
    	deviceI2C->I2CWriteReg16(INA219_REG_CONFIG, config);

    	quantum = _quantum;
	error = false;
     }
     else{
	error = true;
     }
}


// Destructeur
INA219::~INA219()
{
   if (deviceI2C != NULL)
        delete deviceI2C;
}


// Méthode pour fixer la calibration
void INA219::fixerCalibration_16V()
{

    uint16_t config;
    config  = BVOLTAGERANGE_16V | INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT | INA219_CONFIG_SADCRES_12BIT_128S_69MS | INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
    config = ((config & 0x00FF) << 8) | ((config & 0xFF00) >> 8);  // inversion msb lsb
    deviceI2C->I2CWriteReg16(INA219_REG_CONFIG, config);


}


// Méthode pour obtenir la valeur de tension en Volt
float INA219::lireTension_V()
{

    float vb;
    unsigned short data;

    data = deviceI2C->I2CReadReg16(INA219_REG_BUSVOLTAGE);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    //printf("%d\n",data >> 3); // à décommenter pour  évaluer le quantum expérimentalement
    vb = (data >> 3) * quantum/1000.0;  // decalage de 3 bits vers la droite 4.000 mv par bit
    return vb;

}


// Méthode pour obtenir la valeur de tension du shunt en millivolt
float INA219::lireTensionShunt_mV()
{ // la tension aux bornes du shunt 0.01 ohm en mV

    float shuntVoltage;
    short data,vb;

    data = deviceI2C->I2CReadReg16(INA219_REG_SHUNTVOLTAGE);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8);
    shuntVoltage = 9.76E-3 * (float)data;
    return shuntVoltage;
}


// Méthode pour obtenir la valeur de courant en Ampere
float INA219::lireCourant_A()
{

    short data;
    short rc = 4096;
    rc = ((rc & 0x00FF) << 8) | ((rc & 0xFF00) >> 8);
    deviceI2C->I2CWriteReg16(INA219_REG_CALIBRATION , rc);  // écriture du registre de calibration
    data = deviceI2C->I2CReadReg16(INA219_REG_CURRENT);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data * 100E-6;   // 100 micro Ampere par bit

}


// Méthode pour obtenir la valeur de courant moyen en Ampere
float INA219::lireCourantMoyen_A(int nb)
{
  float som = 0.0;
  int i; 
  for(i=0; i < nb; i++){
     som +=  INA219::lireCourant_A();
     usleep(1000*1000);
    }
  cout << i << " : " << fixed << setprecision (3) << som << endl;
  return som / i;
}


// Méthode pour obtenir la valeur de puissance en Watt
float INA219::lirePuissance_W()
{

    short data;

    data = deviceI2C->I2CReadReg16(INA219_REG_POWER);
    data = ((data & 0x00FF) << 8) | ((data & 0xFF00) >> 8); // inversion msb lsb
    return (float)data * 2E-3;     // 2 mW par bit


}


// Fonction pour réaliser une adaptation d'échelle de valeur
float INA219::map(float x, float in_min, float in_max, float out_min, float out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}


// Méthode pour obtenir la valeur de niveau de charge en %
float INA219::lireBatterieSOC(){
     // Rm is the resistance of the metallic path through the cell including the terminals,
     // electrodes and inter-connections.
     // Ra is the resistance of the electrochemical path including the electrolyte and the separator.
     // The internal resistance of a galvanic cell is temperature dependent
     // here I take Ra+Rm = 1.5 Ohm at 25 °C
     float ResistanceInt = 1.5;
     float fem = INA219::lireTension_V() - (ResistanceInt * INA219::lireCourant_A());
     float soc = INA219::map(fem, 8.0, 9.55, 10, 100);
     if (soc > 100) soc = 100;
     if (soc < 0)   soc = 0;
     return soc;

}
