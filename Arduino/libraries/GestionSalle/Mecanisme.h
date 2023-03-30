#ifndef __MECANISME__
#define __MECANISME__

/** Nombre maximum de variable de controle. */
#define NB_VDC_MAX 32

/**
   \file mecanisme.h
*/

#include <arduino.h>
#include "variableDeControle.h"

/**
*   \class Mecanisme
*   \author Sebastien Angibaud
*   \brief Déclaration de la classe Mecanisme décrivant le fonctionnement commun à tous les mécanismes. 
*/
class Mecanisme
{
  public:  
    Mecanisme(int id);
    ~Mecanisme();
      
    void setup();
    void loop();

  protected:
	void ajouterVDC(int id, VariableDeControle::VDCType t, VariableDeControle::VDCSignal s, int pin = VDC_NO_PIN);
    byte getValeurVDC( int id ) const;
	void setValeurVDC( int pin, int valeur );
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
    virtual void updateSorties() = 0; 
	
  private:
    /** \brief L'identifiant du mécanisme. */
    int m_id; 
	
    /** \brief Le tableau des variables de controle. */
	VariableDeControle * m_vdc[NB_VDC_MAX];

    /** \brief L'adresse du mécanisme esclave sur le bus I2C. */
    byte m_slaveAddress;

    /** \brief data_to_echo. */
    static byte m_data_to_echo;
};

#endif // __MECANISME__
