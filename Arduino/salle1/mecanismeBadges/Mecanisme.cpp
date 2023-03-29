/**
 * \file mecanisme.cpp
 */

#include "mecanisme.h"
#include <HardwareSerial.h>
#include <Arduino.h>
#include <Wire.h>

byte Mecanisme::m_data_to_echo = 0;

/**
 * \brief Constructeur de la classe Mecanisme.
 * \param id L'identifiant du mécanisme dans la salle
 */
Mecanisme::Mecanisme( int id )
  : m_id( id ), m_slaveAddress( id + 8 )
{
  
}

/**
 * \brief Méthode appelée par le \b setup de base sur Arduino.
 */
void Mecanisme::setup() 
{
  setupGeneral();
  setupMecanisme();
}

/**
 * \brief Méthode appelée par le \b loop de base sur Arduino.
 */
void Mecanisme::loop() 
{
    loopGeneral();
    loopMecanisme();
}

/**
 * \brief Méthode appelée par le \b setup pour tous les mécanismes.
 */
void Mecanisme::setupGeneral() 
{
  Serial.begin(9600);
  while( ! Serial )
    ;

  for ( int i = 0; i != NB_PIN; ++i )
  {
    m_verrous[ i ] = false;
    m_valeurs_voulues[ i ] = LOW;
  }

  setupI2C();

  Serial.println( "Mecanisme::setup()" );
  Serial.print( "Mecanisme ");
  Serial.print( m_id );  
  Serial.println( " pret." );
}

/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 */
void Mecanisme::loopGeneral() 
{
  serialEvent();
}

/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 * \param pin Le pin à considérer.
 * \param valeur La valeur à écrire.
 */
void Mecanisme::ecrireSortie( int pin, int valeur )
{
  m_valeurs_voulues[ pin ] = valeur;
  
  if ( ! m_verrous[ pin ] )
    digitalWrite( pin, valeur );
}

/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 * \param pin Le pin à considérer.
 * \param valeur La valeur à donner.
 */
void Mecanisme::verrouiller( int pin, int valeur )
{
  m_verrous[ pin ] = true;
  digitalWrite( pin, valeur );    
}
   
/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 * \param pin Le pin à considérer.
 */
void Mecanisme::deverrouiller( int pin )
{
  m_verrous[ pin ] = false;
  digitalWrite( pin, m_valeurs_voulues[ pin ] );
}

void Mecanisme::serialEvent() 
{
  char c = 0; // for incoming serial data
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    c = Serial.read();
    
    switch ( c  )
    {
      case 'V' : verrouiller(14, LOW);
            break;
     
      case 'W' : verrouiller(14, HIGH);
            break;

      case 'D' : deverrouiller(14);
            break;
    };
  }
}

void Mecanisme::setupI2C() 
{
  Wire.begin(m_slaveAddress);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void Mecanisme::receiveData(int bytecount)
{
  for (int i = 0; i < bytecount; i++) {
    m_data_to_echo = Wire.read();
  }
}
void Mecanisme::sendData()
{
  Wire.write(m_data_to_echo);
}

