#ifndef __MECANISME__
#define __MECANISME__

/** Nombre maximum de variable de controle. */
#define NB_VDC_MAX 16
#define TAILLE_BUFFER_I2C 8

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
	void ajouterVDC(int id, VariableDeControle::VDCType t, 
	VariableDeControle::VDCSignal s, int pin = VDC_NO_PIN);
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
	void traiterMessageI2C();

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

    /** \brief Le message recu sur le bus I2C. */
    static byte s_data_I2C[TAILLE_BUFFER_I2C];
	
	/** \brief Indique si les data reçues via l'I2C sont prêtes à être traitée. */
    static bool s_data_I2C_ok;
		
	/** \brief L'état du mécanisme à anevoyer sur le bus I2C. */
    static byte s_etat;
};

#endif // __MECANISME__
