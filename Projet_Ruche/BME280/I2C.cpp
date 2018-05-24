#include "I2C.h"

I2C::I2C(int address, int bus)
{
    char filename[20];
    union i2c_smbus_data data ;

    snprintf(filename, 19, "/dev/i2c-%d", bus);

    if ((fd = open (filename, O_RDWR)) < 0)
    {
        cout << "Erreur d'ouverture du bus I2C" << endl;
        exit(1);
    }

    if (ioctl (fd, I2C_SLAVE, address) < 0)
    {
        cout << "Impossible de sélectionner l'adresse I2C" << endl ;
        exit(1);
    }

    if (i2c_smbus_access (I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
    {
        error = true ;
    }
    else
    {
        error = false ;
    }
}

bool I2C::getError()
{
    return error;
}

int I2C::i2c_smbus_access(char rw, uint8_t command, int size, i2c_smbus_data *data)
{
    struct i2c_smbus_ioctl_data args ;

      args.read_write = rw ;
      args.command    = command ;
      args.size       = size ;
      args.data       = data ;
    return ioctl (fd, I2C_SMBUS, &args) ;
}

unsigned char I2C::I2CRead()
{
    union i2c_smbus_data data;

      if (i2c_smbus_access (I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
        return -1 ;
      else
          return data.byte & 0xFF ;
}

unsigned char I2C::I2CReadReg8(int reg)
{
    union i2c_smbus_data data;

      if (i2c_smbus_access (I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
        return -1 ;
      else
          return data.word & 0xFFFF ;
}

unsigned short I2C::I2CReadReg16(int reg)
{
    union i2c_smbus_data data;

      if (i2c_smbus_access (I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
        return -1 ;
      else
          return data.word & 0xFFFF ;
}


unsigned char I2C::I2CWrite(int data)
{
    return i2c_smbus_access (I2C_SMBUS_WRITE, data, I2C_SMBUS_BYTE, NULL) ;
}

unsigned char I2C::I2CWriteReg8(int reg, int value)
{
    union i2c_smbus_data data ;

    data.byte = value ;
    return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data) ;
}

unsigned short I2C::I2CWriteReg16(int reg, int value)
{
    union i2c_smbus_data data ;

    data.word = value ;
    return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &data) ;
}