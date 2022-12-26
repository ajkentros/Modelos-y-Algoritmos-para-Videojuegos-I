#include "Bullet.h"

using namespace std;
using namespace sf;

//constructor
Bullet::Bullet()
{
	bulletSpeed = 0.f;
}
Bullet::Bullet(Texture* _txt_bullet, float _posPlayerX, float _posPlayerY, float _dirPlayerX, float _dirPlayerY, float _bulletspeed)
{
	this->spr_bullet.setTexture(*_txt_bullet);

	this->spr_bullet.setPosition(_posPlayerX, _posPlayerY);
	this->spr_bullet.setScale(0.5, 0.5);
	this->bulletDirection.x = _dirPlayerX;
	this->bulletDirection.y = _dirPlayerY;
	this->bulletSpeed = _bulletspeed;
}

//destructor
Bullet::~Bullet()
{
	
}

//devuelve el rectángulo del sprite bala
const FloatRect Bullet::getBounds() const
{
	return this->spr_bullet.getGlobalBounds();
}

//asigna movimiento a bullet desde las coordenadas de Player
void Bullet::Update_bullet()
{
	this->spr_bullet.move(this->bulletSpeed * this->bulletDirection);
}

//render bullet desde el Player
void Bullet::RenderBullet(RenderTarget* target)
{
	target->draw(this->spr_bullet);
}
