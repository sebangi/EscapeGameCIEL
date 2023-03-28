/*
   \file MFRC522Daisy.h
*/

#include <SPI.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#define NB_LECTEURS_MAX 10

#define SS_PIN 10
#define RST_PIN 9

/*
   \class MFRC522Daisy
   \author Sebastien Angibaud
   \brief Déclaration de la classe MFRC522Daisy permettant d'utliser plusieursz lecteur MFRC522
   en chainage de type Daisy.

   PINS UTILISES :
      MISO_PIN 12
      MOSI_PIN 11
      SCK_PIN 13
      SS_PIN 10
      RST_PIN 9  LAISSER CE PIN LIBRE
      un PIN RST UNIQUE pour chaque lecteur
*/
class MFRC522Daisy
{
  public:
    MFRC522Daisy( int nb_lecteurs );
    void ajoutLecteur(int numLecteur, int rst_pin);
    bool read( int numLecteur );

  private:
    void selectLecteur(int numLecteur);
    void printHex(byte *buffer, byte bufferSize);

  private:
    MFRC522Extended m_mfrc522; // L'interface du Lecteur
    int m_rstPinLecteurs[ NB_LECTEURS_MAX ]; // La liste des PIN RST de chaque lecteurs
    int m_nb_lecteurs; // Le nombre de lecteurs actuels
};
