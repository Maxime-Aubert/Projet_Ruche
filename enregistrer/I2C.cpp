#include "I2C.h"

// Constructeur
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


// Méthode permettant de lire une donnée
unsigned char I2C::I2CRead()
{
    union i2c_smbus_data data;

      if (i2c_smbus_access (I2C_SMBUS_READ, 0, I2C_SMBUS_BYTE, &data))
        return -1 ;
      else
          return data.byte & 0xFF ;
}


// Méthode permettant de lire une donnée de 8 bits
unsigned char I2C::I2CReadReg8(int reg)
{
    union i2c_smbus_data data;

      if (i2c_smbus_access (I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
        return -1 ;
      else
          return data.word & 0xFFFF ;
}


// Méthode permettant de lire une donnée de 16 bits
unsigned short I2C::I2CReadReg16(int reg)
{
    union i2c_smbus_data data;

      if (i2c_smbus_access (I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
        return -1 ;
      else
          return data.word & 0xFFFF ;
}


// Méthode permettant d’écrire une donnée
unsigned char I2C::I2CWrite(int data)
{
    return i2c_smbus_access (I2C_SMBUS_WRITE, data, I2C_SMBUS_BYTE, NULL) ;
}


// Méthode permettant d’écrire une donnée de 8 bits
unsigned char I2C::I2CWriteReg8(int reg, int value)
{
    union i2c_smbus_data data ;

    data.byte = value ;
    return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data) ;
}


// Méthode permettant d’écrire une donnée de 16 bits
unsigned short I2C::I2CWriteReg16(int reg, int value)
{
    union i2c_smbus_data data ;

    data.word = value ;
    return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &data) ;
}

 int I2C::I2CWriteBlockData (int reg, int length, int *values){
	union i2c_smbus_data data ;
        int i;
        if (length > 32)
	    length = 32;
        for (i = 1; i <= length; i++)
	    data.block[i] = values[i-1];
	data.block[0] = length;
        return i2c_smbus_access (I2C_SMBUS_WRITE, reg, I2C_SMBUS_I2C_BLOCK_BROKEN , &data) ;
}
 
int I2C::I2CReadBlockData (int reg, int length, int *values){
         union i2c_smbus_data data;
         int i;

         if (length > 32)
                 length = 32;
         data.block[0] = length;
         if (i2c_smbus_access(I2C_SMBUS_READ, reg, length == 32 ? I2C_SMBUS_I2C_BLOCK_BROKEN :
                               I2C_SMBUS_I2C_BLOCK_DATA,&data)){
	     error = true;
             return -1;
	 }
         else {
                 for (i = 1; i <= data.block[0]; i++)
                         values[i-1] = data.block[i];
                 return data.block[0];
              }
}

int I2C::delay_ms(unsigned long num_ms)
{
    struct timespec ts;

    ts.tv_sec = num_ms / 1000;
    ts.tv_nsec = (num_ms % 1000) * 1000000;

    return nanosleep(&ts, NULL);
}
