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

MFRC522Daisy monMFRC522(2);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_A, OUTPUT);

  monMFRC522.ajoutLecteur(1, RST1_PIN);
  monMFRC522.ajoutLecteur(2, RST2_PIN);
  
  Serial.begin(9600);
  while( ! Serial )
    ;

  SPI.begin();
  
  Serial.println( F("Scan des lecteurs..."));  
  digitalWrite( LED_PIN, LOW );
}

void loop() {
  if ( monMFRC522.read(1) )
  {   
      digitalWrite( LED_PIN, HIGH );  
      analogWrite( LED_PIN_A, 255 );  
  }

  if ( monMFRC522.read(2) )
    digitalWrite( LED_PIN, HIGH );   
    analogWrite( LED_PIN_A, 255 );    
}
