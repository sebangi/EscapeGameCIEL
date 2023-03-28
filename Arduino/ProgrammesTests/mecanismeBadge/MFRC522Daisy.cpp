/**
 * \file MFRC522Daisy.cpp
 */
 
#include "MFRC522Daisy.h"

/**
 * \brief Constructeur de la classe MFRC522Daisy.
 * \param nb_lecteurs Nombre de lecteurs utilisés.
 */
MFRC522Daisy::MFRC522Daisy( int nb_lecteurs )
{
  m_nb_lecteurs = nb_lecteurs;
}

/**
 * \brief Ajout d'un lecteur.
 * \param numLecteur Le numéro du lecteur.
 * \param rst_pin Le pin reset utilisé pour ce lecteur.
 */
void MFRC522Daisy::ajoutLecteur(int numLecteur, int rst_pin)
{
  pinMode(rst_pin, OUTPUT);
  m_rstPinLecteurs[numLecteur - 1] = rst_pin;
}

/**
 * \brief Lecture d'un badge.
 * \param numLecteur Numero du lecteur sur lequel lire.
 * \return Retourne \b true si un badge est correctement détecté, \b false sinon
 */
bool MFRC522Daisy::read( int numLecteur )
{
  selectLecteur(numLecteur);

  // attente d'une carte RFID
  if ( m_mfrc522.PICC_IsNewCardPresent() )
    // Récupération des informations de la carte RFID
    if ( m_mfrc522.PICC_ReadCardSerial() )
    {
      // Affichage des informations de la carte RFID
      Serial.print("Lecteur ");
      Serial.println(numLecteur);
      //m_mfrc522.PICC_DumpToSerial( &(m_mfrc522.tag) );
      printHex(m_mfrc522.uid.uidByte, m_mfrc522.uid.size);
      
      return true;
    }

  return false;
}

/**
 * \brief Sélectionne un lecteur.
 * \param numLecteur Le numero de lecteur à sélectionner.
 */
void MFRC522Daisy::selectLecteur(int numLecteur)
{
  m_mfrc522.PCD_Reset();

  for (  int i = 0; i != m_nb_lecteurs; ++i )
    digitalWrite( m_rstPinLecteurs[i], (i == numLecteur - 1) );

  m_mfrc522.PCD_Init(SS_PIN, RST_PIN);
}

/**
 * \brief Affiche en hexadécimal un tableau.
 * \param buffer Le tableau de Byte à écrire.
 * \param bufferSize La taille du tableau.
 */
void MFRC522Daisy::printHex(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ?  "0" :  " " );
    Serial.print(buffer[i], HEX);
  }

  Serial.println("");
}
