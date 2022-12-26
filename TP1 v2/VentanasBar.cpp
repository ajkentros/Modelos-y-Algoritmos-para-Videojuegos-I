#include "VentanasBar.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace sf;

//Constructor VentanasBar
VentanasBar::VentanasBar()
{
	ventanaVacia = true;		//flag ventanaVac�a, inicia el jeugo en verdadero (la ventana est� vac�a)
}

//posiciona la ventana en la escena
VentanasBar::VentanasBar(int x, int y)
{
	posicionVentana = Vector2i(x, y);		//posiciona la ventana seg�n coordenadas x e y
}

//flag estado de ventanaVacia
bool VentanasBar::VentanaVacia()
{
	return ventanaVacia;
}

//devuelve la posici�n de la ventana
Vector2i VentanasBar::GetPositionVentana()
{
	return posicionVentana;
}

//setea la posici�n de la ventana en la escena
void VentanasBar::SetPositionVentana(Vector2i position)
{
	posicionVentana = position;		//posiciona la ventana seg�n coordenadas x e y
}

//cambia el flag de ventanaVac�a
void VentanasBar::EstadoVentana()
{
	ventanaVacia = !ventanaVacia;		//invierte el valor del flag ventanaVac�a
}