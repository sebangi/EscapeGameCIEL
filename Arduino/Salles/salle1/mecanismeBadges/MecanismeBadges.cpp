/**
 * \file mecanismeBadges.cpp
 */

#include "mecanismeBadges.h"
#include <HardwareSerial.h>

/**
 * \brief Constructeur de la classe MecanismeBadges.
 */
MecanismeBadges::MecanismeBadges( int id )
  : Mecanisme( id ), m_monMFRC522(2)
{
  
}

/**
 * \brief Méthode appelée par le \b setup de base sur Arduino.
 */
void MecanismeBadges::setupMecanisme() 
{
  Serial.println( "MecanismeBadges::setupMecanisme()" );
  pinMode(LED1_GREEN_PIN, OUTPUT);
  pinMode(LED1_RED_PIN, OUTPUT);
  pinMode(LED2_GREEN_PIN, OUTPUT);
  pinMode(LED2_RED_PIN, OUTPUT);
  pinMode(LED3_GREEN_PIN, OUTPUT);
  pinMode(LED3_RED_PIN, OUTPUT);
  pinMode(LED4_GREEN_PIN, OUTPUT);
  pinMode(LED4_RED_PIN, OUTPUT);
  pinMode(GACHE_PIN, OUTPUT);
  
  m_monMFRC522.ajoutLecteur(1, RST1_PIN, UID_LECTEUR1);
  m_monMFRC522.ajoutLecteur(2, RST2_PIN, UID_LECTEUR2);
  m_monMFRC522.ajoutLecteur(3, RST3_PIN, UID_LECTEUR3);
  m_monMFRC522.ajoutLecteur(4, RST4_PIN, UID_LECTEUR4);

  SPI.begin();
    
  ajouterVDC( ID_VDC_LECTEUR1, VariableDeControle::VDC_IN, VariableDeControle::VDC_DIGITAL );
  ajouterVDC( ID_VDC_LECTEUR2, VariableDeControle::VDC_IN, VariableDeControle::VDC_DIGITAL );
  ajouterVDC( ID_VDC_LECTEUR3, VariableDeControle::VDC_IN, VariableDeControle::VDC_DIGITAL );
  ajouterVDC( ID_VDC_LECTEUR4, VariableDeControle::VDC_IN, VariableDeControle::VDC_DIGITAL );

  ajouterVDC( ID_VDC_GACHE, VariableDeControle::VDC_OUT, VariableDeControle::VDC_DIGITAL, GACHE_PIN );

  Serial.println( F("Scan des lecteurs...")); 
}

/**
 * \brief Méthode appelée par le \b loop de base sur Arduino.
 */
void MecanismeBadges::loopMecanisme() 
{
  setValeurVDC(ID_VDC_LECTEUR1, m_monMFRC522.read(1) );
  setValeurVDC(ID_VDC_LECTEUR2, m_monMFRC522.read(2) );
  setValeurVDC(ID_VDC_LECTEUR3, m_monMFRC522.read(3) );
  setValeurVDC(ID_VDC_LECTEUR4, m_monMFRC522.read(4) );
}

/**
 * \brief Mise à jour des sorties.
 */
void MecanismeBadges::updateSorties()
{
  updateLed(ID_VDC_LECTEUR1, LED1_GREEN_PIN, LED1_RED_PIN);
  updateLed(ID_VDC_LECTEUR2, LED2_GREEN_PIN, LED2_RED_PIN);
  updateLed(ID_VDC_LECTEUR3, LED3_GREEN_PIN, LED3_RED_PIN);
  updateLed(ID_VDC_LECTEUR4, LED4_GREEN_PIN, LED4_RED_PIN);

  if (  getValeurVDC(ID_VDC_LECTEUR1) &&
        getValeurVDC(ID_VDC_LECTEUR2) //&&
        //getValeurVDC(ID_VDC_LECTEUR3) &&
        //getValeurVDC(ID_VDC_LECTEUR4)
         )
    setValeurVDC( ID_VDC_GACHE, 1 );
  else
    setValeurVDC( ID_VDC_GACHE, 0 );
}

/**
 * \brief Gestion d'une lecture et mise à jour des leds.
 * \param id_vdc L'identifiant de la variable de controle (VDC). 
 * \param pin_green Le pin de la led verte à considérer.
 * \param pin_red Le pin de la led verte à considérer.
 */
void MecanismeBadges::updateLed( int id_vdc, int pin_green, int pin_red )
{  
  if ( getValeurVDC(id_vdc) )
  {
    digitalWrite(pin_green, HIGH);
    digitalWrite(pin_red, LOW);
  }
  else
  {
    digitalWrite(pin_green, LOW);
    digitalWrite(pin_red, HIGH);
  }
}
