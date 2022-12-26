#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "VentanasBar.h"


using namespace sf;

//Clase Enemigos
class Enemigos
{
protected:
	bool enemigoVivo;			//Enemigo está vivo
	bool enemigoMostrado;		//Enemigo se muestra en la ventana
	bool enemigoEnVentana;		//Enemigo está en la ventana
	float tiempoVisible;		//tiempo que muestra al Enemigo - dificultad del juego
	float tiempoNoVisible;		//tiempo que no muestra al Enemigo - dificultad del juego

	Texture txt_Enemigo;		//textura Enemigo
		
	Sprite spr_Enemigo;			//Sprite Enemigo
	
	Clock reloj;				//Reloj
	
	VentanasBar* ventanaBar;	//Objeto ventana de la clase VentanasBar




public:
	Enemigos();										//Constructor Enemigos							
	void MostrarEnemigo(VentanasBar* ventanaBar);	//muestra el Enemigo en ventana del bar
	void Draw(RenderWindow* ventanaP);				//dibuja enemigo en vantana del bar
	void UpdateEnemigo();							//actualiza si se muestra el enemigos en función del tiempo visible y no visible
	void EnemigoMuerto();							//si el enemigo es abatido, actualiza el estado de la ventana y del enemigo
	
	bool EnemigoVivo();								//devuelve el estado del flag enemigoVivo
	bool EnemigoMostrado();							//devuelve el estado del flag enemigoMostrado
	bool EnemigoActivo();							//devuelve el estado del flag enemigoVivo y enemigoEnVentana
	bool EnemigoInterceptado(float x, float y);		//devuelve el estado del flag si las coordenadas x e y caen dentro del Sprite Enemigo
	
	virtual bool EnemigoDispara();	//función virtual que retorna verdadero si el enemigo disparó al player
	virtual int Puntos();			//función virtual cuenta puntos logrados por abatir un enemigo
};