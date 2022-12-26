#pragma once
#include "Enemigos.h"


//Sublcase Inocentes de la clase Enemigos
class Inocentes : public Enemigos
	
{
private:


public:
	Inocentes();			//Constructor de clase Inocentes
	int Puntos();			//función cuenta puntos logrados por abatir un inocente
	bool EnemigoDispara();	//función que modifica estado de EnemigoDispara()
	
};




