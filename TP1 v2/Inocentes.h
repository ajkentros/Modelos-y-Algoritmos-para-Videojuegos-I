#pragma once
#include "Enemigos.h"


//Sublcase Inocentes de la clase Enemigos
class Inocentes : public Enemigos
	
{
private:


public:
	Inocentes();			//Constructor de clase Inocentes
	int Puntos();			//funci�n cuenta puntos logrados por abatir un inocente
	bool EnemigoDispara();	//funci�n que modifica estado de EnemigoDispara()
	
};




