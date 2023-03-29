#ifndef __MECANISME__
#define __MECANISME__

#define NB_PIN 22

/**
   \file mecanisme.h
*/

#include <arduino.h>

/**
*   \class Mecanisme
*   \author Sebastien Angibaud
*   \brief Déclaration de la classe Mecanisme décrivant le fonctionnement commun à tous les mécanismes. 
*/
class Mecanisme
{
  public:  
    Mecanisme(int id);
      
    void setup();
    void loop();

  protected:
    void ecrireSortie( int pin, int valeur );
    void verrouiller( int pin, int valeur );
    void deverrouiller( int pin );
    
  private:
    void setupGeneral();
    void loopGeneral();
    void serialEvent();
    void setupI2C();
    static void receiveData(int bytecount);
    static void sendData();

    virtual void setupMecanisme() = 0;  
    virtual void loopMecanisme() = 0;  

  private:
    /** \brief L'identifiant du mécanisme. */
    int m_id; 

    /** \brief Le tableau indiquant quels pins sont verouillées. */
    bool m_verrous[NB_PIN]; 

    /** \brief Le tableau indiquant les valeurs souhaitées dans le mode normal. */
    int m_valeurs_voulues[NB_PIN]; 

    /** \brief L'adresse du mécanisme esclave sur le bus I2C. */
    byte m_slaveAddress;

    /** \brief data_to_echo. */
    static byte m_data_to_echo;
};

#endif // __MECANISME__
