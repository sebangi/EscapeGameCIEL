#ifndef __VariableDeControle__
#define __VariableDeControle__

/**
   \file variableDeControle.h
*/

#include "arduino.h"

#define VDC_NO_PIN  -1

/**
*   \class VariableDeControle
*   \author Sebastien Angibaud
*   \brief Déclaration de la classe VariableDeControle décrivant une variable controlée par le système entier. 
*/
class VariableDeControle
{
  public:
	/** \brief Les différents types de controle. */
	enum VDCType{ VDC_IN, VDC_OUT };

	/** \brief Les différents types de signaux. */
	enum VDCSignal{ VDC_DIGITAL, VDC_ANALOG };
	
	private:
	/** \brief Les différents modes d'utilisation. */
	enum VDCMode{ VDC_NORMAL, VDC_VERROUILLE };
				
  public:  
    VariableDeControle(VDCType t, VDCSignal s, int pin = VDC_NO_PIN); 
	
	byte getValeur() const;
	void setValeur( byte valeur );
    void verrouiller( byte valeur );
    void deverrouiller();
	
  private:
	void write();
    
  private:
    /** \brief Le type de controle. */
    VDCType m_type; 
		
    /** \brief Le type de signal. */
    VDCSignal m_signal; 

	/** \brief Le pin pour l'écriture. */
    int m_pin; 

    /** \brief Indique si la variable de controle est verrouillée (ie. piloté par l'extérieur). */
    VDCMode m_mode; 

    /** \brief La valeur en mode normal. */
    byte m_valeur; 

    /** \brief La valeur en mode verrouillé. */
    byte m_valeur_verrouille; 
};

#endif // __VariableDeControle__
