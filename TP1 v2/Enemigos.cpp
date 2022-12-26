#include "Enemigos.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>

using namespace sf;
using namespace std;

//Constructor Enemigos
Enemigos::Enemigos()
{
	enemigoVivo = true;			//el juego inicia con el flag enemigoVivo = verdadero
	enemigoMostrado = false;	//el juego inicia con el flag enemigoMostrado = falso
	enemigoEnVentana = false;	//el juego inicia con el flag enemigoEnVentana = falso
	tiempoVisible = 2.0f;		//tiempo visible del enemigo
	tiempoNoVisible = 3.5f;		//tiempo no visible del enemigo
	reloj.restart();

	string enemigo = "enemigo" + to_string(rand() % 5 + 1) + ".png";		//inicia el juego seleccionando aleatoriamente un Enemigo

	txt_Enemigo.loadFromFile(enemigo);		//textura del enemigo
	spr_Enemigo.setTexture(txt_Enemigo);	//Sprite del enemigo 
	spr_Enemigo.setOrigin((float) txt_Enemigo.getSize().x / 2, (float) txt_Enemigo.getSize().y);	//configura el origne del Sprite Enemigo con el centro de la textura Enemigo

	ventanaBar = new VentanasBar;		//instancia el objeto ventana de la clase VnetanasBar
}

//devuelve el estado del flag enemigoVivo
bool Enemigos::EnemigoVivo()
{
	return enemigoVivo;

}

//devuelve el estado del flag enemigoMostrado
bool Enemigos::EnemigoMostrado()
{
	return enemigoMostrado;
}

//devuelve el estado del flag enemigoVivo y enemigoEnVentana
bool Enemigos::EnemigoActivo()
{
	return enemigoVivo && enemigoEnVentana;
}

//devuelve el estado del flag si las coordenadas x e y caen dentro del Sprite Enemigo
bool Enemigos::EnemigoInterceptado(float x, float y)
{
	FloatRect limites = spr_Enemigo.getGlobalBounds();	//calcula los límites del rectángulo que forma el Sprite Enemigo
	return limites.contains(x, y);						//flag que comprueba si las coordenadas x e y están dentro del rectángulo del Enemigo
}

//muestra el Enemigo en ventana del bar
void Enemigos::MostrarEnemigo(VentanasBar* ventanasBar)
{
	if (!enemigoMostrado)		//Si el enemigo no mostrado =>
	{
		ventanaBar = ventanasBar;	
		enemigoMostrado = true;			//se activa el flag enemigoMostrado
		enemigoEnVentana = true;		//se activa el flag enemigoEnVentana
		ventanaBar->EstadoVentana();	//se llama a la función de la clase Ventanas Bar para cambiar el estado del flag ventanaVacía
		spr_Enemigo.setPosition((Vector2f)ventanaBar->GetPositionVentana());		//se posiciona el Sprite Enemigo en la posición de la ventana
		reloj.restart();		//se establece el tiempo del reloj
	}
}
//dibuja enemigo en pantalla
void Enemigos::Draw(RenderWindow* ventanaP)	
{
	if (enemigoMostrado)	//si está libre la ventana =>
	{
		ventanaP->draw(spr_Enemigo);		//dibuja enemigo en pantalla
	}

}

//actualiza estado del enemigo en vantana del bar
void Enemigos::UpdateEnemigo()	
{
	if (enemigoVivo)		//si flag enemigoVivo = verdadero =>
	{
		if (enemigoMostrado && reloj.getElapsedTime().asSeconds() > tiempoVisible) //si el tiempoVisble se superó y flag enemigoMostrado = true
		{
			enemigoMostrado = false;		//flag enemigoMostrado = falso
			reloj.restart();				//se restablece el tiempo del reloj
			return;							
		}
		if (!enemigoMostrado && reloj.getElapsedTime().asSeconds() > tiempoNoVisible)	//si el tiempoNoVisible se superó y enemigo mostrado = true
		{
			enemigoMostrado = true;			//flag enemigoMostrado = verdadero
			reloj.restart();				//se restablece el tiempo del reloj
			return;
		}
	}
}

//si el enemigo es abatido, actualiza el estado de la ventana y del enemigo
void Enemigos::EnemigoMuerto()
{
	enemigoVivo = false;			//flag enemigoVivo = falso
	enemigoMostrado = false;		//flag enemigoMostrado = falso
	ventanaBar->EstadoVentana();	//se llama a la función de la clase Ventanas Bar para cambiar el estado del flag ventanaVacía
}

//función que retorna verdadero si el enemigo disparó al player
bool Enemigos::EnemigoDispara()
{
	bool disparo = false;

	if (enemigoMostrado)				//si enemigo se muestra en la ventana
	{
		disparo = rand() % 100 < 20;	//= verdadero, si el número aleatorio < 20 (el enemigo disparó al player), la probabilidad es de 20/100
	}

	return disparo;
}

//función virtual cuenta puntos logrados por abatir un enemigo
int Enemigos::Puntos()
{
	return 1;	//suma 1 punto por cada enemigo abatido
}

