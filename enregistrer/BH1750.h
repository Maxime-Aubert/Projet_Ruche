    #ifndef BH1750_H_INCLUDED
    #define BH1750_H_INCLUDED

    #include "I2C.h"
    #include <unistd.h>

    #define ADRESSE_BH1750 0x23  // Adresse I2C du capteur BH1750


    #define BH1750_POWER_DOWN 0x00


    #define BH1750_POWER_ON 0x01


    #define BH1750_RESET 0x07


    #define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10


    #define BH1750_CONTINUOUS_HIGH_RES_MODE_2  0x11

    #define BH1750_CONTINUOUS_LOW_RES_MODE  0x13

    #define BH1750_ONE_TIME_HIGH_RES_MODE  0x20

    #define BH1750_ONE_TIME_HIGH_RES_MODE_2  0x21

    #define BH1750_ONE_TIME_LOW_RES_MODE 0x23

    class BH1750 {
    public:
        // Le constructeur
        BH1750(int addressBH1750=ADRESSE_BH1750);

        // Le destructeur
        ~BH1750();
        float lireEclairement_Lux();

        // Méthode pour configurer le mode
        void configurer(int mode=BH1750_ONE_TIME_HIGH_RES_MODE_2);
        void activer(void);
        void desactiver(void);
        void reset(void);
    private:
        I2C *deviceI2C;
        float resolution;  

    };

    #endif /* BH1750_H */
