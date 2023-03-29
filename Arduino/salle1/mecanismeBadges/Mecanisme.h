#ifndef __MECANISME__
#define __MECANISME__

#define NB_PIN 22

/**
   \file mecanisme.h
*/

/**
*   \class Mecanisme
*   \author Sebastien Angibaud
*   \brief Déclaration de la classe Mecanisme décrivant le fonctionnement commun à tous les mécanismes. 
*/
class Mecanisme
{
  public:  
    Mecanisme(int id);
      
    void setup();
    void loop();

  protected:
    void ecrireSortie( int pin, int valeur );
    void verrouiller( int pin, int valeur );
    void deverrouiller( int pin );
    
  private:
    void setupGeneral();
    void loopGeneral();
    void serialEvent();

    virtual void setupMecanisme() = 0;  
    virtual void loopMecanisme() = 0;  

  private:
    /** \brief L'identifiant du mécanisme. */
    int m_id; 

    /** \brief Le tableau indiquant quels pins sont verouillées. */
    bool m_verrous[NB_PIN]; 

    /** \brief Le tableau indiquant les valeurs souhaitées dans le mode normal. */
    int m_valeurs_voulues[NB_PIN]; 
};

#endif // __MECANISME__
