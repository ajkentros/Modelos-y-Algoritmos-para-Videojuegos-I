#include "VentanasBar.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;

//Constructor VentanasBar
VentanasBar::VentanasBar()
{
	ventanaVacia = true;		//flag ventanaVacía, inicia el jeugo en verdadero (la ventana está vacía)
}

//posiciona la ventana en la escena
VentanasBar::VentanasBar(int x, int y)
{
	posicionVentana = Vector2i(x, y);		//posiciona la ventana según coordenadas x e y
}

//flag estado de ventanaVacia
bool VentanasBar::VentanaVacia()
{
	return ventanaVacia;
}

//devuelve la posición de la ventana
Vector2i VentanasBar::GetPositionVentana()
{
	return posicionVentana;
}

//setea la posición de la ventana en la escena
void VentanasBar::SetPositionVentana(Vector2i position)
{
	posicionVentana = position;		//posiciona la ventana según coordenadas x e y
}

//cambia el flag de ventanaVacía
void VentanasBar::EstadoVentana()
{
	ventanaVacia = !ventanaVacia;		//invierte el valor del flag ventanaVacía
}