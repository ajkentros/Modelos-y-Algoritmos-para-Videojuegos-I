#include "Enemy.h"

using namespace std;
using namespace sf;

//inicia variables
void Enemy::InitVariables()
{
	/*
		enemyCount define entre 3 a 10 tipos de enemigos distintos
		enemySpeed en funci�n de enemyCount/3 min=1, max=10/3
		vidaMax = enemyCount
		vida = vidaMax
		puntos = enemyCount
	*/
	this->enemyCount = rand() % 8 + 3; //l�mite inferior = 3 l�mite superior = 10 
	this->enemySpeed = static_cast<float>(this->enemyCount/3);
	this->damage = this->enemyCount;
	this->puntos = this->enemyCount;
}
//inicia enemy
void Enemy::InitEnemy()
{
	/*
		define radio de enemy en funci�n de enemyCount
		define el n�mero de lados del CircleShape
		define el color de enemy
	*/
	this->enemy.setRadius((float) this->enemyCount * 3);
	this->enemy.setPointCount(this->enemyCount);
	this->enemy.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}
//constructor Enemy
Enemy::Enemy(float _posX, float _posY)
{
	/*
		inicia variables
		inicia Enemy en la posicion x e y de la pantalla
	*/
	this->InitVariables();
	this->InitEnemy();
	
	this->enemy.setPosition(_posX, _posY);
	positionX = _posX;
	positionY = _posY;
}
//destructor Enemy
Enemy::~Enemy()
{

}
//return rect�ngulo del sprite enemy
const FloatRect Enemy::getBounds() const
{
	return this->enemy.getGlobalBounds();
}
//return puntos
const int &Enemy::getPuntos() const
{
	return this->puntos;
}
//return da�o
const int &Enemy::getDamage() const
{
	return this->damage;
}

//actualiza enemy
void Enemy::UpdateEnemy()
{
	/*
		mueve enemy en el eje y (verticlamente) a la velocidad enemySpeed en funci�n del typo de enemy
	*/
	this->enemy.move(0.f, this->enemySpeed);
}
//render enemy en la ventana
void Enemy::RenderEnemy(RenderTarget* target)
{
	target->draw(this->enemy);
}
