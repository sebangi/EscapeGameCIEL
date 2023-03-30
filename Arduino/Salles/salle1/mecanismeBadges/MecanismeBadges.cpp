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

  m_monMFRC522.ajoutLecteur(1, RST1_PIN, UID_LECTEUR1);
  m_monMFRC522.ajoutLecteur(2, RST2_PIN, UID_LECTEUR2);
  m_monMFRC522.ajoutLecteur(3, RST3_PIN, UID_LECTEUR3);
  m_monMFRC522.ajoutLecteur(4, RST4_PIN, UID_LECTEUR4);

  SPI.begin();
  
  Serial.println( F("Scan des lecteurs..."));  
  ecrireSortie( LED1_GREEN_PIN, LOW );
  ecrireSortie( LED1_RED_PIN, HIGH );
  ecrireSortie( LED2_GREEN_PIN, LOW );
  ecrireSortie( LED2_RED_PIN, HIGH );
  ecrireSortie( LED3_GREEN_PIN, LOW );
  ecrireSortie( LED3_RED_PIN, HIGH );
  ecrireSortie( LED4_GREEN_PIN, LOW );
  ecrireSortie( LED4_RED_PIN, HIGH );  
}

/**
 * \brief Méthode appelée par le \b loop de base sur Arduino.
 */
void MecanismeBadges::loopMecanisme() 
{
  int nb_lu = 0;
  
  nb_lu = nb_lu + gererLecteur( 1, LED1_GREEN_PIN, LED1_RED_PIN );
  nb_lu = nb_lu + gererLecteur( 2, LED2_GREEN_PIN, LED2_RED_PIN );
  nb_lu = nb_lu + gererLecteur( 3, LED3_GREEN_PIN, LED3_RED_PIN );
  nb_lu = nb_lu + gererLecteur( 4, LED4_GREEN_PIN, LED4_RED_PIN );
   
  Serial.print("\t\tNb lu = ");
  Serial.println( nb_lu );
}

/**
 * \brief Gestion d'une lecture et mise à jour des leds.
 * \param numLecteur Le numéro du lecteur à lire.
 * \param pin_green Le pin de la led verte à utiliser.
 * \param pin_red Le pin de la led rouge à utiliser. 
 * \return Return \b true si le lecteur a reconnu le bon badge.
 */
bool MecanismeBadges::gererLecteur( int numLecteur, int pin_green, int pin_red ) 
{  
  if ( m_monMFRC522.read(numLecteur) )
  {
    ecrireSortie(pin_green, HIGH);
    ecrireSortie(pin_red, LOW);
    return true;
  }
  else
  {
    ecrireSortie(pin_green, LOW);
    ecrireSortie(pin_red, HIGH);
    return false;
  }    
}
