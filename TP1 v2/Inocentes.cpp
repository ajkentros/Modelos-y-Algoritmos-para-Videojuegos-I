#include "Inocentes.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//Constructor de clase Inocentes
Inocentes::Inocentes()
{
	enemigoVivo = true;			//Inocente vivo
	enemigoMostrado = false;	//Inocente no se muestra
	enemigoEnVentana = false;	//Inocente no está en la ventana
	tiempoVisible = 1.0f;		//tiempo que muestra el Inocente - dificultad del juego
	tiempoNoVisible = 3.5f;		//tiempo que no muestra el Inocente - dificultad del juego
	reloj.restart();			//Inicio del reloj
	txt_Enemigo.loadFromFile("inocente.png");	//Textura del Inocente
	spr_Enemigo.setTexture(txt_Enemigo);		//Sprite del Inocente
	spr_Enemigo.setOrigin((float) txt_Enemigo.getSize().x / 2, (float) txt_Enemigo.getSize().y);	//oirgen del Sprite Inocente en el centro de la textura
}

//función cuenta puntos logrados por abatir un inocente
int Inocentes::Puntos()
{
	return -10;	//resta 10 puntos por cada inocente abatido
}

//función que modifica estado de EnemigoDispara() de la clase Enemigos
bool Inocentes::EnemigoDispara()
{
	return false;	//retorna falso porque el Inocente no dispara

}