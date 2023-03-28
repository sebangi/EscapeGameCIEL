#ifndef __MECANISME_BADGES__
#define __MECANISME_BADGES__

/**
   \file mecanisme_badges.h
*/

#include "mecanisme.h"
#include "MFRC522Daisy.h"
#include "defines.h"

/**
*   \class MecanismeBadges
*   \author Sebastien Angibaud
*   \brief Déclaration de la classe pour gérer le mécanisme des badges RFID. 
*/
class MecanismeBadges : public Mecanisme
{
  public:  
    MecanismeBadges( int id );

  private:
    void setupMecanisme();
    void loopMecanisme();
    void gererLecteur( int numLecteur, int pin_green, int pin_red ) ;

  private:
    /** \brief Interface de l'ensemble des lecteurs MFRC522 en mode Daisy. */
    MFRC522Daisy m_monMFRC522;
};

#endif // __MECANISME_BADGES__
