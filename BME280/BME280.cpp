#include "BME280.h"
#include "I2C.h"

using namespace std;

// Constructeur
BME280::BME280(int addressBME280)
{
    deviceI2C = new I2C(addressBME280);
        if (!deviceI2C->getError())
        {
            readCalibrationData();
            deviceI2C->I2CWriteReg8(0xF2, 0x01);

            deviceI2C->I2CWriteReg8(0xF4, 0x27);
            h = -78.0;
            error = false;
        }
        else
        {
            error = true;
        }
}


// Destructeur
BME280::~BME280()
{
    if (deviceI2C != NULL)
        delete deviceI2C;
}

// Méthode lisant les constantes de calibrations
void BME280::readCalibrationData()
{
    calib.dig_T1 = (uint16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_T1);
    calib.dig_T2 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_T2);
    calib.dig_T3 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_T2);

    calib.dig_P1 = (uint16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P1);
    calib.dig_P2 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P2);
    calib.dig_P3 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P3);
    calib.dig_P4 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P4);
    calib.dig_P5 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P5);
    calib.dig_P6 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P6);
    calib.dig_P7 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P7);
    calib.dig_P8 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P8);
    calib.dig_P9 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_P9);

    calib.dig_H1 = (uint8_t)deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H1);
    calib.dig_H2 = (int16_t)deviceI2C->I2CReadReg16(BME280_REGISTER_DIG_H2);
    calib.dig_H3 = (uint8_t)deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H3);
    calib.dig_H4 = (deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H4) << 4) | (deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H4+1) & 0xF);
    calib.dig_H5 = (deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H5+1) << 4) | (deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H5) >> 4);
    calib.dig_H6 = (int8_t)deviceI2C->I2CReadReg8(BME280_REGISTER_DIG_H6);
}

// Méthode permettant d’obtenir les données brut
void BME280::getRawData()
{
    deviceI2C->I2CWrite(0xf7);


    raw.pmsb = deviceI2C->I2CRead();
    raw.plsb = deviceI2C->I2CRead();
    raw.pxsb = deviceI2C->I2CRead();

    raw.tmsb = deviceI2C->I2CRead();
    raw.tlsb = deviceI2C->I2CRead();
    raw.txsb = deviceI2C->I2CRead();

    raw.hmsb = deviceI2C->I2CRead();
    raw.hlsb = deviceI2C->I2CRead();

    raw.temperature = 0;
    raw.temperature = (raw.temperature | raw.tmsb) << 8;
    raw.temperature = (raw.temperature | raw.tlsb) << 8;
    raw.temperature = (raw.temperature | raw.txsb) >> 4;

    raw.pressure = 0;
    raw.pressure = (raw.pressure | raw.pmsb) << 8;
    raw.pressure = (raw.pressure | raw.plsb) << 8;
    raw.pressure = (raw.pressure | raw.pxsb) >> 4;

    raw.humidity = 0;
    raw.humidity = (raw.humidity | raw.hmsb) << 8;
    raw.humidity = (raw.humidity | raw.hlsb);
}


// Méthode permettant d’obtenir les constantes de calibrations de la température
int32_t BME280::getTemperatureCalibration()
{
    getRawData();

    int32_t var1  = ((((raw.temperature>>3) - ((int32_t)calib.dig_T1 <<1))) * ((int32_t)calib.dig_T2)) >> 11;

    int32_t var2  = (((((raw.temperature>>4) - ((int32_t)calib.dig_T1)) * ((raw.temperature>>4) - ((int32_t)calib.dig_T1))) >> 12) *
                ((int32_t)calib.dig_T3)) >> 14;
    return var1 + var2;
}

// Méthode pour obtenir la valeur de température en degré Celsius
float BME280::lireTemperature_DegreCelsius()
{
    int32_t t_fine = getTemperatureCalibration();
    float T_Celsius  = (t_fine * 5 + 128) >> 8;
    return T_Celsius/100;
}

// Méthode pour obtenir la valeur de température en degré Fahrenheit
float BME280::lireTemperature_Fahrenheit()
{
    float T_Celsius = lireTemperature_DegreCelsius();
    float T_Fahrenheit = (T_Celsius * 9) /5 + 32;
    return T_Fahrenheit;
}

// Méthode pour obtenir la valeur de pression en hPa
float BME280::lirePression()
{
    int32_t t_fine = getTemperatureCalibration();
    int64_t var1, var2, p;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)calib.dig_P6;
    var2 = var2 + ((var1*(int64_t)calib.dig_P5)<<17);
    var2 = var2 + (((int64_t)calib.dig_P4)<<35);
    var1 = ((var1 * var1 * (int64_t)calib.dig_P3)>>8) + ((var1 * (int64_t)calib.dig_P2)<<12);
    var1 = (((((int64_t)1)<<47)+var1))*((int64_t)calib.dig_P1)>>33;
    if (var1 == 0)
    {
      return 0;
    }
    p = 1048576 - raw.pressure;
    p = (((p<<31) - var2)*3125) / var1;
    var1 = (((int64_t)calib.dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((int64_t)calib.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)calib.dig_P7)<<4);
    return (float)p/25600;
}

// Méthode pour obtenir la valeur d'humidité relative en %
float BME280::lireHumidite()
{
    int32_t v_x1_u32r;
    int32_t t_fine = getTemperatureCalibration();


    v_x1_u32r = (t_fine - ((int32_t)76800));
    v_x1_u32r = (((((raw.humidity << 14) - (((int32_t)calib.dig_H4) << 20) - (((int32_t)calib.dig_H5) * v_x1_u32r)) +
                ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)calib.dig_H6)) >> 10) * (((v_x1_u32r *
                ((int32_t)calib.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
                ((int32_t)calib.dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calib.dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
    v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
    float h = (v_x1_u32r>>12);
    return h / 1024.0;
}
