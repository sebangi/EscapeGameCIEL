/**
 * \file variableDeControle.cpp
 */

#include "variableDeControle.h"

/**
 * \brief Constructeur de la classe VariableDeControle.
 * \brief t Le type (entrée ou sortie).
 * \brief s Le type de signal (digital ou analog).
 * \brief pin Le pin à utiliser pour l'écriture.
 */
VariableDeControle::VariableDeControle(VDCType t, VDCSignal s, int pin)
	: m_type(t), m_signal(s), m_pin(pin), m_mode(VDC_NORMAL)
{
	m_valeur = 0; 
    m_valeur_verrouille = 0; 
}

/**
 * \brief Accesseur de la valeur.
 * \return La valeur actuelle (celle du sytème en mode nomrla ou celle imposée en mode verrouillage).
 */
byte VariableDeControle::getValeur() const
{
	if ( m_mode == VDC_NORMAL )
		return m_valeur;
	else
		return m_valeur_verrouille;
}
	
/**
 * \brief Initialise la valeur du mode normal.
 * \param valeur La valeur voulue.
 */
void VariableDeControle::setValeur( byte valeur )
{
  m_valeur = valeur;
  write();
}

/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 * \param pin Le pin à considérer.
 * \param valeur La valeur à donner.
 */
void VariableDeControle::verrouiller( byte valeur )
{
  m_valeur_verrouille = valeur;
  m_mode = VDC_VERROUILLE;
  write();    
}
   
/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 * \param pin Le pin à considérer.
 */
void VariableDeControle::deverrouiller()
{
  m_mode = VDC_NORMAL;
  write();
}

/**
 * \brief Mise à jour de la sortie.
 */
void VariableDeControle::write()
{
	if ( m_type == VDC_OUT && m_pin != VDC_NO_PIN )
	{
		byte valeur;
		if ( m_mode == VDC_NORMAL )
			valeur = m_valeur;
		else
			valeur = m_valeur_verrouille;

		if ( m_signal == VDC_DIGITAL )
			digitalWrite( m_pin, valeur );
		else
			analogWrite( m_pin, valeur );
	}
}
