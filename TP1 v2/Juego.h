#pragma once

#include <iostream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Enemigos.h"
#include "VentanasBar.h"
#include "Inocentes.h"

using namespace sf;
using namespace std;

class Juego
{

private:
	RenderWindow* ventanaP;		//ventana principal del juego

	Texture tex_Fondo;			//Textura del fondo
	Sprite spr_Fondo;			//Sprite del fondo

	Texture tex_Mira;			//Textura de la mira
	Sprite spr_Mira;			//Sprite de la mira

	VentanasBar ventanasBar[5];	//objeto ventanasBar como vector de 1x5 para las 5 ventanas

	Clock reloj;				//reloj

	int vidas;					//vidas del player
	int puntos;					//puntos logrados por el player
	int inocentesTotales = 2;	//cantidad de inocentes que se pueden eliminar (dificultad del juego)
	int enemigosTotales = 15;	//cantidad de enemigos totales a eliminar (dificultad del juego)
	float tiempoDisparo;		//tiempo de disparo del player

	list<Enemigos*> enemigos;	//lista de enemigos, objeto Enemigos

	Text tex_Puntos;			//texto para Puntos
	Text tex_Enemigos;			//texto para Enemigos
	Text tex_Vidas;				//texto para Vidas
	Text tex_Resultado;			//texto para Resultado
	Font fon_Fuente;			//fuente

	SoundBuffer sb_Disparo;		//bufer sonido del disparo
	SoundBuffer sb_Abatido;		//bufer sonido del Player abatido

	Sound sonido_Disparo;		//sonido del disparo
	Sound sonido_Abatido;		//sonido del player abatido


public:
	Juego();						//Constructor de clase Juego
	void Loop();					//loop del juego
	void InciaVentanaP();			//inicia ventana principal
	void IniciaTexto();				//inicia texto en pantalla
	void IniciaSonidos();			//inicia sonidos
	void IniciaMira();				//inicia mira
	
	void DrawJuego();				//dibuja elementos del juego
	void GestorEventos();			//detecta si se cierra ventana + verifica colisiones
	void UpdateJuego();				//actualiza posición de mira = posición del mouse + actualiza enemigos
	
	void IniciaVentanaBar();		//inicia ventanas del bar
	
	void GeneraEnemigos();				//genera los enemigos según cantidad de ventanas libres (dificultad del juego)
	void IniciaEnemigos();				//inicia Enemigos
	void DrawEnemigos();				//dibuja enemigos en pantalla
	void UpdateEnemigos();				//actualiza estado del enemigo en vantana del bar

	void VerificaColisiones();			//verifica si colisiona la mira con el sprite del enemigo/inocente

	void UpdatePuntos(int _puntos);		//actualiza puntos y los muestra en pantalla
	void UpdateVidas();					//muestra las vidas en pantalla

	void DisparaAlJugador();			//función diminuye vidas si dispara el enemigo
	void PantallaGameOver(int _cuenta);			//función inicia pantalla de fin de juego

	int GetCuentaEnemigosVivos();		//cuenta y retorna la cantidad de enemigos vivos
	int GetCuentaVentanasBarVacias();	//cuenta ventanas vacías = sin enemigos sin inocentes
	


	Enemigos* GetEnemigosInactivos();	//objeto Enemigos, informa los enemigos inactivos = no activo y si vivo




};


