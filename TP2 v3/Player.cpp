#include "Player.h"

using namespace std;
using namespace sf;

void Player::InitVariables()
{
	/*
		velocidad inicial de player = 2
		atequeMax = 10
		ataque = ataqueMax
		vidamax = 100 (vidas de player)
		vida = vidaMax
	*/
	//this->playerSpeed = 0.f;
	this->ataqueMax = 10.f;				//define frecuencia de lanzamiento de bullet por ataque del Player
	this->ataque = this->ataqueMax;

	this->vidaMax = 100;				//define vidas máximas del player
	this->vida = this->vidaMax;
}

void Player::InitPlayer()
{	
	/*
		carga textura de player
		define spr_player con textura
		escala player
		posiciona player en el abajo y centro de la pantalla
	*/
	
	if (!this->tex_player.loadFromFile("player.png"))
	{
		cout << "No se puede abrir player.png" << "\n";
	}
		
	this->spr_player.setTexture(this->tex_player);
	this->spr_player.scale(0.05f, 0.05f);
	this->spr_player.setPosition(400.0f, 500.0f);
}
//constructor player
Player::Player()
{
	/*
		inicia las variables
		inicia player
	*/
	this->InitVariables();
	this->InitPlayer();
}
//destructor
Player::~Player()
{

}
//return posición de player
Vector2f Player::getPosition()
{
	return this->spr_player.getPosition();
}
//return rectángulo del sprite de player
FloatRect Player::getBounds()
{
	return this->spr_player.getGlobalBounds();
}
//return vida de player
const int &Player::getVida() const
{
	return this->vida;
}
//return vidaMax de player
const int &Player::getVidaMax() const
{
	return this->vidaMax;
}
//return bool puede atacar
const bool Player::canAtaque()
{
	/*
		return true y ataque = 0 si ataque >= ataqueMax (recibidos por enemy)
		return false
	*/
	if (this->ataque >= this->ataqueMax)
	{
		this->ataque = 0.f;
		return true;
	}

	return false;
}
//modifica posición de player
void Player::setPosition(const Vector2f _positionPlayer)
{
	this->spr_player.setPosition(_positionPlayer);
}
//modifica posición de player
void Player::setPosition(const float _x, const float _y)
{
	this->spr_player.setPosition(_x, _y);
}
//modifica vidaMax de player
void Player::setVida(const int _vida)
{
	this->vida = _vida;
}
void Player::setVidaMax(const int _vida)
{
	this->vidaMax = _vida;
}
//modifica vida de player (pierde vida)
void Player::LoseVida(const int _valor)
{
	this->vida -= _valor;
	if (this->vida < 0)
		this->vida = 0;
}
//modifica ataque
void Player::UpdateAtaque()
{
	/*
		si ataque < ataqueMax, ataque se incrementa
	*/
	if(this->ataque < this->ataqueMax)
		this->ataque += 1.f;
}
//actualiza player
void Player::UpdatePlayer()
{
	this->UpdateAtaque();
}
//render el player en pantalla
void Player::RenderPlayer(RenderTarget& target)
{
	target.draw(this->spr_player);
}
