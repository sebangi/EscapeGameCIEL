#ifndef __APPLICATION__
#define __APPLICATION__

/**
   \file application.h
*/

#include "MFRC522Daisy.h"

#define RST1_PIN 7
#define RST2_PIN 8
#define LED_PIN 19
#define LED_PIN_A A6

// MISO_PIN 12
// MOSI_PIN 11
// SCK_PIN 13
// SS_PIN 10 
// RST_PIN 9  A LAISSER LIBRE

/**
*   \class Application
*   \author Sebastien Angibaud
*   \brief Déclaration de la classe Application décrivant le fonctionnement globale de l'application. 
*/
class Application
{
  public:  
    Application();  
    void setup();
    void loop();

  private:
    /** \brief Interface de l'ensemble des lecteurs MFRC522 en mode Daisy. */
    MFRC522Daisy m_monMFRC522;
};

#endif // __APPLICATION__
