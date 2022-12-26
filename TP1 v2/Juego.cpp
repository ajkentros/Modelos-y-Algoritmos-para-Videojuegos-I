#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Juego.h"

using namespace sf;
using namespace std;

//Constructor de clase Juego
Juego::Juego()
{
	
	puntos = 0;				//inicia el juego con puntos = 0
	vidas = 3;				//inicia el juego con 3 vidas del player
	tiempoDisparo = 12.0f;	//dificultad del juego tiempo de dispar del player
	reloj.restart();		//inicia el reloj /clock)

	
	InciaVentanaP();		//Inicia la ventana principal del juego
	IniciaTexto();			//Inicia el texto
	IniciaSonidos();		//Inicia los sonidos
	IniciaMira();			//inicia la mira
	IniciaVentanaBar();		//inicia las ventanas del bar
	IniciaEnemigos();		//inicia los enemigos

}

//Inicia la ventana principal del juego
void Juego::InciaVentanaP()
{
	//inicia ventana Principal del juego y coloca fondo de bar
	ventanaP = new RenderWindow(VideoMode(780, 438), "TP1");
	ventanaP->setMouseCursorVisible(false);		//desactiva el cursor del mause

	tex_Fondo.loadFromFile("fondo.png");		//textura del fondo
	spr_Fondo.setTexture(tex_Fondo);			//Sprite del fondo
}

//Inicia el texto
void Juego::IniciaTexto()
{
	//define fuente, texto de Puntos, Vida y Game Over
	fon_Fuente.loadFromFile("BACKCOUNTRY-Regular.ttf");

	//posiciona texto Puntos con su fuente tamaño y color
	tex_Puntos.setFont(fon_Fuente);
	tex_Puntos.setPosition(56, 410);
	tex_Puntos.setString("PUNTOS: ");
	tex_Puntos.setCharacterSize(20);
	tex_Puntos.setOutlineColor(Color::White);

	//posiciona tecto Enemigos con su fuente y color
	tex_Enemigos.setFont(fon_Fuente);
	tex_Enemigos.setPosition(410, 410);
	tex_Enemigos.setString("ENEMIGOS: ");
	tex_Enemigos.setCharacterSize(20);
	tex_Enemigos.setOutlineColor(Color::White);

	//posiciona texto Vidas con su fuente tamaño y color
	tex_Vidas.setFont(fon_Fuente);
	tex_Vidas.setPosition(250, 410);
	tex_Vidas.setString("VIDAS: 3");
	tex_Vidas.setCharacterSize(20);
	tex_Vidas.setOutlineColor(Color::White);

	//posiciona texto Resultado con su fuente tamaño y color
	tex_Resultado.setFont(fon_Fuente);
	tex_Resultado.setPosition(100, 100);
	tex_Resultado.setString("GAME OVER");
	tex_Resultado.setCharacterSize(20);
	tex_Resultado.setOutlineColor(Color::White);
}

//Inicia sonidos de disparo y player abatido
void Juego::IniciaSonidos()
{
	//sonido del disparo
	sb_Disparo.loadFromFile("disparo.wav");
	sonido_Disparo.setBuffer(sb_Disparo);

	//sonido de player abatido
	sb_Abatido.loadFromFile("abatido.wav");
	sonido_Abatido.setBuffer(sb_Abatido);

}

//inicia del mira
void Juego::IniciaMira()
{
	tex_Mira.loadFromFile("miraBlanca.png");	//textura de la mira

	spr_Mira.setTexture(tex_Mira);				//sprite de la mira
	spr_Mira.setScale(0.03f, 0.03f);			//escaldo de la mira
	spr_Mira.setColor(Color::White);			//color de la mira
	spr_Mira.setOrigin((float)tex_Mira.getSize().x / 2, (float)tex_Mira.getSize().y / 2);	//origen de la mira en el centro de la textura

}

//inicia ventanas del bar
void Juego::IniciaVentanaBar()
{
	//define lugares de las ventanas del bar
	ventanasBar[0] = VentanasBar(165, 163);
	ventanasBar[1] = VentanasBar(609, 163);
	ventanasBar[2] = VentanasBar(131, 367);
	ventanasBar[3] = VentanasBar(630, 367);
	ventanasBar[4] = VentanasBar(388, 367);
}

//inicia Enemigos
void Juego::IniciaEnemigos()
{
	for (int i = 0; i <= enemigosTotales; i++) //por cada enemigo del total hacer:
	{
		bool inocente = rand() % 100 <= 35;	//probabilidad de aparición de inocentes = 35%

		if (inocente && inocentesTotales > 0)		//si flags inocentes y inocentesTotales > 0, salió un inocente y quedan vivos dos =>
		{
			enemigos.push_back(new Inocentes());	//inserta un objeto Inocente al final de la lista enemigos (si aparece un inocente)
			inocentesTotales--;						//disminuye inocentes totales cuando se instancia un inocente
		}
		else
		{
			enemigos.push_back(new Enemigos());		//inserta un objeto Enemigo al final de la lista enemigos (si no aparece un inocente)
		}
	}
}

//loop del juego
void Juego::Loop()
{
	while (ventanaP->isOpen()) //mientras no se cierre el juego (ventana) se ejecuta
	{
		if (GetCuentaEnemigosVivos() > 0 && vidas > 0) //si la cantidad de enemigos vivos > 0 y las vidas > 0 hacer:
		{
			GestorEventos();	//detecta si se cierra ventana + verifica colisiones
			UpdateJuego();		//actualiza posición de mira = posición del mouse + actualiza enemigos
			GeneraEnemigos();	//genera los enemigos según cantidad de ventanas libres (dificultad del juego)
			DrawJuego();		//dibuja juego en pantalla
		}
		else
		{
			PantallaGameOver(enemigosTotales);	//función inicia pantalla de fin de juego
			Event evento1;
			while (ventanaP->pollEvent(evento1))		//mientras se detecte un evento
			{
				if (evento1.type == Event::Closed)		//si el evento es cerrar ventana =>
				{
					ventanaP->close();					//cerrar ventana
					exit(1);							//salir 
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape) == true)	//si el evento es clic en Escape
				{
					ventanaP->close();					//cerrar ventana
					exit(1);							//salir 
				}
			}
		}
	}

}

//cuenta y retorna la cantidad de enemigos vivos
int Juego::GetCuentaEnemigosVivos()	
{
	int cuenta = 0;


	for (Enemigos* e : enemigos)	//for each por cada objeto que enemigos que está en la lista, se guarda en la variable Enemigos e
	{
		if (e->EnemigoVivo() && e->Puntos() > 0)	//si el enemigo está vivo y los puntos > 0 =>
		{
			cuenta++;								//incermeta en 1 el contador 
		}
	}
	
	return cuenta;
}

//detecta si se cierra ventana + verifica colisiones
void Juego::GestorEventos()
{
	Event evento2;
	while (ventanaP->pollEvent(evento2))	//mientras se detecte un evento hacer:
	{
		switch (evento2.type)
		{
		case Event::Closed:			//hace clic en la x de la ventana
			ventanaP->close();		//cierra ventana
			break;
		case Event::MouseButtonPressed:		//hace clic en un botón del mouse
			if (evento2.mouseButton.button == Mouse::Button::Left)		//hace clic en botón izquierdo del mouse
			{
				sonido_Disparo.play();	//inicia el sonido de disparo
				VerificaColisiones();	//verifica si colisiona la mira con el sprite del enemigo/inocente
			}
		}
	}
}

//verifica si colisiona la mira con el sprite del enemigo/inocente
void Juego::VerificaColisiones()
{
	//Vector2f playerPosicion = mira.GetPositionMira(); //toma la posición de la mira
	Vector2f playerPosicion = spr_Mira.getPosition();

	int _cuentaEnemigos = GetCuentaEnemigosVivos();

	for (Enemigos* e : enemigos)		//for each por cada objeto Enemigo en la lista enemigos
	{
		if (e->EnemigoActivo() && e->EnemigoMostrado() && e->EnemigoInterceptado(playerPosicion.x, playerPosicion.y)) //si el enemigo está activo y se muestra y fue interceptado, hacer:
		{
			int _puntos = e->Puntos();	//actualiza puntos si se mata a un inicente o dispara el enemigo
			UpdatePuntos(_puntos);		//actualiza puntos y los muestra en pantalla
			e->EnemigoMuerto();			//si el enemigo es abatido, actualiza el estado de la ventana y del enemigo
			
			if (_puntos < 0)			//si _puntos <0 actualiza vidas si se mata a un inicente o dispara el enemigo
			{
				vidas--;			//decremeta en 1 la vida del player
				
				UpdateVidas();		//actualiza las vidas totales
			}
		}
	}
}

//actualiza posición de mira = posición del mouse + actualiza enemigos
void Juego::UpdateJuego()	
{
	
	Vector2i mousePosicion = Mouse::getPosition(*ventanaP);		//toma posicion del mouse ne la pantalla principal
	spr_Mira.setPosition((Vector2f)Mouse::getPosition(*ventanaP));				//actualiza posición de la mira = posición del mouse
	UpdateEnemigos();											//actualiza enemigos

}

//dibuja elementos del juego
void Juego::DrawJuego()	//dibuja juego en pantalla
{
	ventanaP->clear(Color::Black);	//limpia pantalla principal
	DrawEnemigos();					//función dibuja enemigos
	ventanaP->draw(spr_Fondo);		//dibuja fondo en pantalla principal
	ventanaP->draw(spr_Mira);		//dibuja mira en pantalla principal
	
	ventanaP->draw(tex_Puntos);		//dibuja texto Puntos en pantalla principal
	ventanaP->draw(tex_Vidas);		//dibuja texto Vidas en pantalla principal
	ventanaP->draw(tex_Enemigos);		//dibuja texto Puntos en pantalla principal
	ventanaP->display();			//muestra en pantalla principal
	
}

//genera los enemigos según cantidad de ventanas libres (dificultad del juego)
void Juego::GeneraEnemigos()
{
	bool _enemigo = rand() % 200 == 50;		//flag probabilidad de aparición del enemigo = 1/200
	int ventanasLibres = 3;					//ventanas libres que deben quedar

	if (_enemigo && GetCuentaVentanasBarVacias() >= ventanasLibres)	//si salió un enemigo y las ventanas vacías > ventanas libres
	{
		int indice = rand() % 5;		//se elige una ventana al azar
		if(ventanasBar[indice].VentanaVacia())	//si la ventana esta vacía = el flag = true
		{
			Enemigos* enemigo = GetEnemigosInactivos();	//informa los enemigos inactivos = no activo y si vi
			if (enemigo != nullptr)
			{
				enemigo->MostrarEnemigo(&ventanasBar[indice]);	//muestra el enemigo en la ventana seleccionada en el indice
			}
		}
	}
}

//dibuja enemigos en pantalla
void Juego::DrawEnemigos()	
{
	for(Enemigos* e : enemigos)		//for each por cada enemigo de la lista enemigos
	{
		if (e->EnemigoMostrado())  //si flag enemigoMostrado = verdadero
		{
			e->Draw(ventanaP);		//dibuja enemigo en pantalla principal
		}
	}

}

//actualiza enemigos
void Juego::UpdateEnemigos()	
{
	for (Enemigos* enemy:enemigos)		//for each por cada enemigo en la lista enemigos
	{
		enemy->UpdateEnemigo();			//dibuja enemigo en vantana del bar

		if (reloj.getElapsedTime().asSeconds() > tiempoDisparo && enemy->EnemigoActivo() && enemy->EnemigoDispara())	//si el tiempo es mayor que el tiempo de diaparo del enemigo y el enemigo está activo y el enemigo dispara
		{
			DisparaAlJugador();	//función diminuye vidas si dispara el enemigo
			reloj.restart();	//restaura el tiempo del reloj
		}
	}
}

//función diminuye vidas si dispara el enemigo
void Juego::DisparaAlJugador()	
{
	sonido_Abatido.play();		//reproduce sonido de player abatido
	vidas--;					//decrementa en 1 la vida del player
	UpdateVidas();				//muestra vidas en pantalla
}

//actualiza puntos y los muestra en pantalla
void Juego::UpdatePuntos(int _puntos)
{
	puntos += _puntos;				//toma los puntos logrados
	string pt = to_string(puntos);	//string de puntos logrados para mostrar en pantalla
	
	int _cuentaEnemigos = GetCuentaEnemigosVivos();
	string cta = to_string(_cuentaEnemigos);
		
	tex_Puntos.setString("PUNTOS: " + pt);	//texto Puntos actualizado con los puntos logrados
	
	tex_Enemigos.setString("ENEMIGOS: " + cta);
}

//muestra las vidas en pantalla
void Juego::UpdateVidas()	
{
	
	string life = to_string(vidas);			//string de vidas para mostrar en pantalla
	tex_Vidas.setString("VIDAS: "+ life);	//c//string vidas para mostrar en pantalla
}

//cuenta ventanas vacías = sin enemigos sin inocentes
int Juego::GetCuentaVentanasBarVacias() 
{
	int count = 0;

	for (int i = 0; i < 5; i++)		//recorre las 5 elementos del vector ventanasBar 
	{
		if (ventanasBar[i].VentanaVacia())	//si está vacía =>
		{
			count++;	//cuenta la cantidad de ventanas vacías
		}
	}

	return count;
}

//informa los enemigos inactivos = no activo y si vivo
Enemigos* Juego::GetEnemigosInactivos()	
{
	for (Enemigos* e : enemigos)	//for each de la lista enemigos
	{
		if (!e->EnemigoActivo() && e->EnemigoVivo())	//si flag enemigoVivo y enemigoEnVentana y flag enemigoVivo
		{
			return e;	//retorna el objeto enemigo
		}
	}

	return nullptr;	//retorna lista vacía
}

//función inicia pantalla de fin de juego
void Juego::PantallaGameOver(int _cuenta)	//inicia pantalla de fin de juego
{
	ventanaP->clear();	//limpia pantalla principal

	if (vidas > 0)		//si hay vidas del player
	{
		tex_Resultado.setString("HAS MATADO A UN TOTAL DE " + to_string(_cuenta) + " ENEMIGOS ");	//Player a ganado, mensaje en pantalla 
		
	}
	

	ventanaP->setMouseCursorVisible(true);	//activa el cursor del mouse
	tex_Puntos.setPosition(100, 200);		//posiciona texto Puntos
	ventanaP->draw(tex_Puntos);				//dibuja texto Puntos en pantalla principal
	ventanaP->draw(tex_Resultado);			//dibuja texto Resultado en pantalla principal
	ventanaP->display();					//muestra en pantalla principal
}