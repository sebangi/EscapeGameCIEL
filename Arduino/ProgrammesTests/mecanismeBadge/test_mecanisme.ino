/**
   \file test_mecanisme.h
   \brief Programme principal de l'application Arduino.
*/

#include "mecanismeBadges.h"

#define MECANISME_BADGES 1

MecanismeBadges meca( MECANISME_BADGES );

/**
 * \brief Méthode \b setup de base sur Arduino.
 */
void setup() 
{
  meca.setup();
}

/**
 * \brief Méthode \b loop de base sur Arduino.
 */
void loop() 
{
  meca.loop();
}
