#pragma once
#include <iostream>
#include <ctime>
#include <map>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"


using namespace std;
using namespace sf;

class Game
{
private:
	//ventana
	RenderWindow* window;

	//Evento
	Event event;

	//mapa pares (string , Texturas)
	map<string, Texture*> textures;
	
	//vector de objetos bullet
	vector<Bullet*> bullets;
	
	//interfaz de usuario					
	Font txt_font;
	Text txt_puntos;
	Text txt_help;
	Text txt_gameOver;
	Text txt_play;
	Text txt_quit;
	Text txt_ganaste;
	RectangleShape playerBarraVida;
	RectangleShape playerBarraVidaBack;

	//Mundo
	Texture tex_mundo;
	Sprite spr_mundo;
	
	//lógica Game
	unsigned puntos;
	float dt;
	float vidaPorcentaje;
	bool menuActivo;
	bool ganaste;
	bool gameOver;
	Clock* reloj1;
	Time tiempo1;
	
	//Player
	Player* player;
	SoundBuffer bufferDisparo;		//bufer sonido del disparo
	Sound sonidoDisparo;			//sonido del disparo

	//Enemies
	float enemyTimer;
	float enemyTimerMax;
	vector<Enemy*> enemy;
	SoundBuffer bufferImpacto;		//bufer sonido enemy impactado
	Sound sonidoImpacto;			//sonido del enemy impactado

	//inicia variables
	void InitVariables();
	//inicia ventana
	void InitWindow();
	//inicia textura
	void InitTextures();
	//inicia sonidos
	void InitSonidos();
	//inicia interfaz de usuario GUI
	void InitGUI();
	//inicia mundo
	void InitMundo();
	//inicia player
	void InitPlayer();
	//inicia enemy
	void InitEnemy();

public:
	//constructor y destructor Game
	Game();
	virtual ~Game();

	//loop de Game
	void LoopGame();
	//escucha eventos
	void PollEvents();
	//actualiza entradas
	void UpdateInput();
	//actualiza interfaz de usuario
	void UpdateGUI();
	//actualiza bullets
	void UpdateBullet();
	//actualiza enemy
	void UpdateEnemy(float _dt);
	//actualiza colisiones en combate
	void UpdateCollision();
	//actualiza Game
	void UpdateGame(float _dt);
	//renderiza GIU
	void RenderGUI();
	//renderiza Mundo
	void RenderMundo();
	//renderiza Game
	void RenderGame();
	//renderiza Menu
	void RenderMenu();
	//renderiza ganaste
	void RenderGanaste();
	//renderiza game over
	void RenderGameOver();
	
};

