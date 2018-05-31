#ifndef I2C_H
#define I2C_H


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <iostream>


#define I2C_SLAVE       0x0703
#define I2C_ACK_TEST    0x0710
#define I2C_SMBUS       0x0720

#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

#define I2C_SMBUS_QUICK     0
#define I2C_SMBUS_BYTE      1
#define I2C_SMBUS_BYTE_DATA 2
#define I2C_SMBUS_WORD_DATA 3
#define I2C_SMBUS_PROC_CALL 4

#define I2C_SMBUS_BLOCK_DATA        5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7
#define I2C_SMBUS_I2C_BLOCK_DATA    8

#define I2C_SMBUS_BLOCK_MAX 	32
#define I2C_SMBUS_I2C_BLOCK_MAX	32

using namespace std;

union i2c_smbus_data
{
  uint8_t  byte ;
  uint16_t word ;
  uint8_t  block [I2C_SMBUS_BLOCK_MAX + 2] ;
};

struct i2c_smbus_ioctl_data
{
  char read_write ;
  uint8_t command ;
  int size ;
  union i2c_smbus_data *data ;
};


class I2C
{
public:
    // Le constructeur
    I2C(int address, int bus=1);

    unsigned char I2CRead(); // Méthode permettant de lire une donnée
    unsigned char I2CReadReg8(int reg); // Méthode permettant de lire une donnée de 8 bits
    unsigned short I2CReadReg16(int reg); // Méthode permettant de lire une donnée de 16 bits
    int I2CReadBlockData (int reg, int length, int *values);

    bool getError();

    unsigned char I2CWrite(int data); // Méthode permettant d’écrire une donnée
    unsigned char I2CWriteReg8(int reg, int value); // Méthode permettant d’écrire une donnée de 8 bits
    unsigned short I2CWriteReg16(int reg, int value); // Méthode permettant d’écrire une donnée de 16 bits
    int I2CWriteBlockData (int reg, int length, int *data);
    int delay_ms(unsigned long num_ms);

private:
inline int i2c_smbus_access (char rw, uint8_t command, int size, union i2c_smbus_data *data);
int fd;
bool error;

};

#endif // I2C_H
