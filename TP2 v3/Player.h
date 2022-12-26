#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class Player
{
private:
	//textura y sprite de player
	Texture tex_player; 
	Sprite spr_player;
	
	//velicidad, ataque, ataque máximo de player
	float playerSpeed;
	float ataque;
	float ataqueMax;
	int vida;
	int vidaMax;

	//Inicia variables de player
	void InitVariables();
	//inicia player
	void InitPlayer();

public:
	//constructor y destructor de playar
	Player();
	virtual ~Player();

	//return posición de player
	Vector2f getPosition();
	//return rectángulo del sprite de player
	FloatRect getBounds();
	//return vida de player
	const int& getVida() const;
	//return vidaMax de player
	const int& getVidaMax() const;
	//return bool puede atacar
	const bool canAtaque();
	//modifica posición de player
	void setPosition(const Vector2f _positionPlayer);
	//modifica posición de player
	void setPosition(const float _x, const float _y);
	//modifica vida de player
	void setVida(const int _vida);
	//modifica vidaMax del player
	void setVidaMax(const int _vida);
	//modifica vida de player (pierde vida)
	void LoseVida(const int _valor);
	//modifica ataque
	void UpdateAtaque();
	//actualiza player
	void UpdatePlayer();
	//render player
	void RenderPlayer(RenderTarget& target);
};

