#ifndef __DEFINES__
#define __DEFINES__

//############## PIN #####################
#define RST1_PIN 5
#define RST2_PIN 6
#define RST3_PIN 7
#define RST4_PIN 8

#define LED1_GREEN_PIN 14
#define LED1_RED_PIN 15

#define LED2_GREEN_PIN 16
#define LED2_RED_PIN 17

#define LED3_GREEN_PIN 20
#define LED3_RED_PIN 21

#define LED4_GREEN_PIN 2
#define LED4_RED_PIN 3

#define GACHE_PIN 4

//----- POUR I2C : ------
// SDA A4 = 18
// SCL A5 = 20

//----- POUR SPI : ------
// MISO_PIN 12
// MOSI_PIN 11
// SCK_PIN 13
// SS_PIN 10 
// RST_PIN 9  A LAISSER LIBRE
//########################################


//####### ID VARIABLES DE CONTROLE ########
#define ID_VDC_LECTEUR1 1
#define ID_VDC_LECTEUR2 2
#define ID_VDC_LECTEUR3 3
#define ID_VDC_LECTEUR4 4
#define ID_VDC_GACHE 5
//########################################


//############## UID #####################
const byte UID_LECTEUR1[4] = {0x6C, 0x5B, 0x7B, 0x6E};
const byte UID_LECTEUR2[4] = {0x43, 0x36, 0x17, 0xD3};
const byte UID_LECTEUR3[4] = {0xFF, 0xFF, 0xFF, 0xFF};
const byte UID_LECTEUR4[4] = {0xFF, 0xFF, 0xFF, 0xFF};
//########################################

#endif // __DEFINES__
