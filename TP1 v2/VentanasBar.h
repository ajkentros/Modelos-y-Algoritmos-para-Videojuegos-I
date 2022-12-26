#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//Clase VentanasBar
class VentanasBar
{
private:
	bool ventanaVacia = true;				//flag ventanaVacía, inicia el jeugo en verdadero (la ventana está vacía)
	Vector2i posicionVentana;		//posición de la ventana en un vector 2D

public:
	VentanasBar();					//Cosntructor VentanasBar
	VentanasBar(int x, int y);		//posiciona la ventana en la escena
	
	void SetPositionVentana(Vector2i position);		//setea la posición de la ventana en la escena
	void EstadoVentana();							//cambia el flag de ventanaVacía	
		
	bool VentanaVacia();							//flag estado de ventanaVacia

	Vector2i GetPositionVentana();					//devuelve la posición de la ventana




};
