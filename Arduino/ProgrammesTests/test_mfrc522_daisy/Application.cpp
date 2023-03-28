/**
 * \file application.cpp
 */

#include "application.h"

/**
 * \brief Constructeur de la classe Application.
 */
Application::Application( )
  : m_monMFRC522(2)
{
  
}



/**
 * \brief Méthode appelée par le \b setup de base sur Arduino.
 */
void Application::setup() 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_A, OUTPUT);

  m_monMFRC522.ajoutLecteur(1, RST1_PIN);
  m_monMFRC522.ajoutLecteur(2, RST2_PIN);
  
  Serial.begin(9600);
  while( ! Serial )
    ;

  SPI.begin();
  
  Serial.println( F("Scan des lecteurs..."));  
  digitalWrite( LED_PIN, LOW );
}

/**
 * \brief Méthode appelée par le \b loop de base sur Arduino.
 */
void Application::loop() 
{
  if ( m_monMFRC522.read(1) )
  {   
      digitalWrite( LED_PIN, HIGH );  
      analogWrite( LED_PIN_A, 255 );  
  }

  if ( m_monMFRC522.read(2) )
    digitalWrite( LED_PIN, HIGH );   
    analogWrite( LED_PIN_A, 255 );    
}
