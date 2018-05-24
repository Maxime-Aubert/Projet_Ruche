/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INA219.h
 * Author: maubert
 *
 * Created on 23 avril 2018, 11:37
 */

#ifndef INA219_H
#define INA219_H

#include <iostream>
#include <iomanip>
#include "I2C.h"
#include <stdint.h>
#include <math.h>
#include <unistd.h>

#define ADRESSE_INA219                          0x40

#define INA219_READ                             0x01

#define INA219_REG_CONFIG                       0x00

#define INA219_REG_SHUNTVOLTAGE                 0x01
#define INA219_REG_BUSVOLTAGE                   0x02
#define INA219_REG_POWER                        0x03
#define INA219_REG_CURRENT                      0x04
#define INA219_REG_CALIBRATION                  0x05

#define BVOLTAGERANGE_MASK                      0x2000
#define BVOLTAGERANGE_16V                       0x0000
#define BVOLTAGERANGE_32V                       0x2000

#define INA219_CONFIG_GAIN_MASK                 0x1800

#define INA219_CONFIG_GAIN_1_40MV               0x0000
#define INA219_CONFIG_GAIN_2_80MV               0x0800 
#define INA219_CONFIG_GAIN_4_160MV              0x1000
#define INA219_CONFIG_GAIN_8_320MV              0x1800

#define INA219_CONFIG_BADCRES_MASK              0x0780

#define INA219_CONFIG_BADCRES_9BIT              0x0000
#define INA219_CONFIG_BADCRES_10BIT             0x0080
#define INA219_CONFIG_BADCRES_11BIT             0x0100
#define INA219_CONFIG_BADCRES_12BIT             0x0180

#define INA219_CONFIG_SADCRES_MASK              0x0078

#define INA219_CONFIG_SADCRES_9BIT_1S_84US      0x0000
#define INA219_CONFIG_SADCRES_10BIT_1S_148US    0x0008  
#define INA219_CONFIG_SADCRES_11BIT_1S_276US    0x0010 
#define INA219_CONFIG_SADCRES_12BIT_1S_532US    0x0018 
#define INA219_CONFIG_SADCRES_12BIT_2S_1060US   0x0048
#define INA219_CONFIG_SADCRES_12BIT_4S_2130US   0x0050 
#define INA219_CONFIG_SADCRES_12BIT_8S_4260US   0x0058 
#define INA219_CONFIG_SADCRES_12BIT_16S_8510US  0x0060
#define INA219_CONFIG_SADCRES_12BIT_32S_17MS    0x0068
#define INA219_CONFIG_SADCRES_12BIT_64S_34MS    0x0070
#define INA219_CONFIG_SADCRES_12BIT_128S_69MS   0x0078

#define INA219_CONFIG_MODE_MASK                 0x0007

#define INA219_CONFIG_MODE_POWERDOWN            0x0000
#define INA219_CONFIG_MODE_BVOLT_TRIGGERED      0x0002
#define INA219_CONFIG_MODE_SANDBVOLT_TRIGGERED  0x0003
#define INA219_CONFIG_MODE_ADCOFF               0x0004
#define INA219_CONFIG_MODE_SVOLT_CONTINUOUS     0x0005
#define INA219_CONFIG_MODE_BVOLT_CONTINUOUS     0x0006
#define INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS 0x0007

class INA219
{

    public:
    // le constructeur
    INA219(int addressINA219=ADRESSE_INA219, float _quantum=3.991);
    // le destructeur
    ~INA219();
    
    float lireTension_V();
    float lireCourant_A();
    float lireCourantMoyen_A(int nb);
    float lirePuissance_W();
    float lireTensionShunt_mV();
    float lireBatterieSOC();
    void  fixerCalibration_16V();

    private:
    I2C *deviceI2C;                   
    bool  error;
    float quantum;		      
    float shunt;		      
    // Fonction pour réaliser une adaptation d'échelle de valeur
    float map(float x, float in_min, float in_max, float out_min, float out_max);
};

#endif /* INA219_H */
