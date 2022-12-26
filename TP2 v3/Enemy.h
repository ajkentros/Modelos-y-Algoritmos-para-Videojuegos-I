#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class Enemy
{
private:
	//enemigo en forma de circulo
	CircleShape enemy;
	
	//variables
	unsigned enemyCount;
	//tipo enemy
	int enemyType;
	//velocidad enemy
	float enemySpeed;
	//posición enemy en Y
	float positionX, positionY;
	//daño
	int damage;
	//puntos
	int puntos;

	//inicia variables
	void InitVariables();
	//inicia enemy
	void InitEnemy();

public:
	Enemy(float _posX, float _posY);
	virtual ~Enemy();

	//return rectángulo del sprite enemy
	const FloatRect getBounds() const;
	//return puntos
	const int& getPuntos() const;
	//return daño
	const int& getDamage() const;
	//actualiza enemy
	void UpdateEnemy();
	//render enemy en la ventana
	void RenderEnemy(RenderTarget* target);
};
