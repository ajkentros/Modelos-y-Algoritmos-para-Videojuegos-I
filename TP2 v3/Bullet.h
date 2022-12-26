#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class Bullet
{
private:
	//sprite de la bala
	Sprite spr_bullet;	

	//vector dirección de la bala
	Vector2f bulletDirection;

	//velocidad de la bala
	float bulletSpeed;

public:
	//constructor y destructor
	Bullet();
	Bullet(Texture* _txt_bullet, float _posX, float _posY, float _dirX, float _dirY, float _bulletspeed);
	virtual ~Bullet();

	//métodos accesorios
	const FloatRect getBounds() const;

	//métodos
	void Update_bullet();
	void RenderBullet(RenderTarget* target);
};

