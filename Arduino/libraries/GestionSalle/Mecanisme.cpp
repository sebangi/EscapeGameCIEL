/**
 * \file mecanisme.cpp
 */

#include "mecanisme.h"
#include <HardwareSerial.h>
#include <Arduino.h>
#include <Wire.h>

// Variables statiques
byte Mecanisme::s_data_I2C[TAILLE_BUFFER_I2C];
bool Mecanisme::s_data_I2C_ok = false;
byte Mecanisme::s_etat = 0;

/**
 * \brief Constructeur de la classe Mecanisme.
 * \param id L'identifiant du mécanisme dans la salle
 */
Mecanisme::Mecanisme( int id )
  : m_id( id ), m_slaveAddress( id + 8 )
{
	for ( int i = 0; i != NB_VDC_MAX; ++i )
		m_vdc[i] = NULL;
}

/**
 * \brief Destructeur de la classe Mecanisme.
 */
Mecanisme::~Mecanisme()
{
	for ( int i = 0; i != NB_VDC_MAX; ++i )
		if ( m_vdc[i] != NULL )
			delete m_vdc[i];
}


/**
 * \brief Méthode appelée par le \b setup de base sur Arduino.
 */
void Mecanisme::setup() 
{
	Serial.println( "Mecanisme::setup()" );
  	
	setupGeneral();
	setupMecanisme();
	
	updateSorties();
   
	Serial.print( "Mecanisme ");
	Serial.print( m_id );  
	Serial.println( " pret." );
}

/**
 * \brief Méthode appelée par le \b loop de base sur Arduino.
 */
void Mecanisme::loop() 
{
    loopGeneral();
    loopMecanisme();
	updateSorties();
}

/**
 * \brief Ajoute une variable de controle.
 * \brief id L'identifiant de la variable de controle (nombre entre 0 et NB_VDC_MAX).
 * \brief t Le type de la variable(entrée ou sortie).
 * \brief s Le type de signal (digital ou analog).
 * \brief pin Le pin à utiliser pour l'écriture.
 */
 void Mecanisme::ajouterVDC(int id, VariableDeControle::VDCType t, VariableDeControle::VDCSignal s, int pin)
{
	if ( id >= 0 && id < NB_VDC_MAX )
		m_vdc[ id ] = new VariableDeControle(t, s, pin);
}    

/**
 * \brief Méthode appelée par le \b setup pour tous les mécanismes.
 */
void Mecanisme::setupGeneral() 
{
  Serial.begin(9600);
  while( ! Serial )
    ;

  setupI2C();
}

/**
 * \brief Méthode appelée par le \b loop pour tous les mécanismes.
 */
void Mecanisme::loopGeneral() 
{
  serialEvent();
  traiterMessageI2C();
}

/**
 * \brief Accesseur d'une valeur d'une variable de controle.
 * \param pin Le pin à considérer.
 * \return La valeur actuelle (celle du sytème en mode nomrla ou celle imposée en mode verrouillage).
 */
byte Mecanisme::getValeurVDC( int id ) const
{
	if ( m_vdc[ id ] != NULL  )
		return m_vdc[ id ]->getValeur();
	else
		return 0;
}

/**
 * \brief Initialise une variable de controle.
 * \param id L'id de la variable à considérer.
 * \param valeur La valeur à écrire.
 */
void Mecanisme::setValeurVDC( int id, int valeur )
{
	if ( m_vdc[ id ] != NULL  )
		m_vdc[ id ]->setValeur( valeur );
}

/**
 * \brief Vérouille une variable de controle.
 * \param id L'id de la variable à considérer.
 * \param valeur La valeur à donner.
 */
void Mecanisme::verrouiller( int id, int valeur )
{
	if ( m_vdc[ id ] != NULL  )
		m_vdc[ id ]->verrouiller( valeur );
}
   
/**
 * \brief Déverouille un variable de controle.
 * \param id L'id de la variable à considérer.
 */
void Mecanisme::deverrouiller( int id )
{
	if ( m_vdc[ id ] != NULL  )
		m_vdc[ id ]->deverrouiller();
}

/**
 * \brief Méthode appelée automatiquement lorsque l'on recoit un message sur le port série.
 */
void Mecanisme::serialEvent() 
{
  char c = 0; // for incoming serial data
  char last = 0;

  if (Serial.available() > 0) {
    // read the incoming byte:
    c = Serial.read();
    
    switch ( c )
    {
      case 'V' : verrouiller(14, LOW);
            last = c;
            break;
     
      case 'W' : verrouiller(14, HIGH);
            last = c;
            break;

      case 'D' : deverrouiller(14);
            last = c;
            break;
    };
  }

  if ( last != 0 )
  {
    Serial.print("Ordre par port série : ");
    Serial.println((char)last);
  }    
}

/**
 * \brief Méthode aintialisant le bus I2C.
 */
void Mecanisme::setupI2C() 
{
  Wire.begin(m_slaveAddress);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

/**
 * \brief Méthode appelée quand on reçoit un message depuis le bus I2C.
 * \param bytecount Le nombre de bytes reçus.
 */
void Mecanisme::receiveData(int bytecount)
{	
	//if ( bytecount > 1 )
	{
		int i;
		Serial.print("bytecount = ");
		Serial.println(bytecount);
	
		for (i = 0; i < bytecount; i++)
		{
			byte b = Wire.read();
			
			if ( i < TAILLE_BUFFER_I2C && bytecount > 1 )
				s_data_I2C[i] = b;
		} 
	
		if ( bytecount > 1 )
			for ( ; i!= TAILLE_BUFFER_I2C; ++i)
				s_data_I2C[i] = 0;	

		for ( i = 0; i!= TAILLE_BUFFER_I2C; ++i)
		{
			Serial.print(s_data_I2C[i]);
			Serial.print(" ");
		}
		Serial.println("");
		
		s_data_I2C_ok = true;
	}
}

/**
 * \brief Méthode appelée automatiquement après avoir lu un message depuis le bus I2C.
 */
void Mecanisme::sendData()
{
	Serial.println("Envoi sur I2C : A");
  	Wire.write( s_etat );
}
/**
 * \brief Traitement d'un message depuis le bus I2C.
 */
void Mecanisme::traiterMessageI2C()
{
	if ( s_data_I2C_ok )
	{
		Serial.print("traiterMessageI2C()");
		for ( int i = 0; i!= TAILLE_BUFFER_I2C; ++i)
		{
			Serial.print(s_data_I2C[i]);
			Serial.print(" ");
		}
		Serial.println("");
		
		Serial.print("TRAITEMENT : ");
		Serial.print(s_data_I2C[1]);
		Serial.print(" : ");		
		
		switch ( s_data_I2C[1] )
		{
			case 1: 
				Serial.println("GET ETATS");
				break;
			case 2: 
				Serial.print("VERROUILLER ");
				Serial.print( s_data_I2C[2] );
				Serial.print( " val = " );
				Serial.println( s_data_I2C[3] );
				
				verrouiller(s_data_I2C[2], s_data_I2C[3]);
				break;
			case 3: 
				Serial.print("DEVERROUILLER ");
				Serial.println( s_data_I2C[2] );
				
				deverrouiller(s_data_I2C[2]);
				break;
		};
		
		s_etat = getValeurVDC(5);
		s_data_I2C_ok = false;
	}
}

