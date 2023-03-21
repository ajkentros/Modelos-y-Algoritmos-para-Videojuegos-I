#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

//inicia ventana
void Game::InitWindow()
{
	/*
		define ventana de juego 800 x 600
		habilta el límite de frame = 60
		deshabilita el sincronismo vertical
	*/
	this->window = new RenderWindow(VideoMode(800, 600), "AKE_TP2", Style::Close | Style::Titlebar);
	this->window->setMouseCursorVisible(false);
	this->window->setFramerateLimit(60);

}
//inicia texturas
void Game::InitTextures()
{
	/*
		inicia el objeto mapa 
		carga en el objeto mapa ("BULLET" y la textura de bullet)
	*/
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("bullet.png");
}
//inicia sonidos
void Game::InitSonidos()
{
	/*
		inicia buffer del disparo
		inicia sonido disparo
		inicia buffer del impacto
		inicia sonido impacto
	*/

	//sonido del disparo
	if (!this-bufferDisparo.loadFromFile("disparo.ogg"))
	{
		cout << "error al cargar el buffer disparo.ogg";
	}
	this->sonidoDisparo.setBuffer(this->bufferDisparo);
	this->sonidoDisparo.setVolume(50.f);

	//sonido de player abatido
	if (!this->bufferImpacto.loadFromFile("impacto.ogg"))
	{
		cout << "error al cargar el buffer impacto.ogg";
	}
	this->sonidoImpacto.setBuffer(this->bufferImpacto);
	this->sonidoImpacto.setVolume(50.f);
}
//inicia interfaz de usuario GIU
void Game::InitGUI()
{
	/*
		carga de fuente
		inicia el texto puntos (fuente, tamaño de la fuente, posición, color, texto)
		inicia el texto gameOver (fuente, tamaño de la fuente, posición, color, texto)
		inicia la barra de vida (tamaño, color, posición)
		inicia la barra de vida back (tamaño, color = transparente, posición)
	*/

	if (!this->txt_font.loadFromFile("ethn.otf"))
		cout << "ERROR::GAME::Failed to load font" << "\n";

	//carga texto puntos
	this->txt_puntos.setFont(this->txt_font);
	this->txt_puntos.setCharacterSize(15); 
	this->txt_puntos.setPosition(600.f, 25.f);
	this->txt_puntos.setFillColor(Color::White);
	this->txt_puntos.setString("puntos");

	//carga barra de vida
	this->playerBarraVida.setSize(Vector2f(200.f, 25.f));
	this->playerBarraVida.setFillColor(Color::Red);
	this->playerBarraVida.setPosition(Vector2f(20.f, 20.f));

	this->playerBarraVidaBack = this->playerBarraVida;
	this->playerBarraVidaBack.setFillColor(Color(25, 25, 25, 200));
	
	//carga texto help
	this->txt_help.setFont(this->txt_font);
	this->txt_help.setCharacterSize(20);
	this->txt_help.setFillColor(Color::White);
	this->txt_help.setString("movimientos -> con mouse \n\n dispara -> con mouse left \n\n ganas -> con 1000 puntos \n\n perdes -> sin vidas");
	this->txt_help.setPosition(
		this->window->getSize().x / 3.f - this->txt_help.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f - this->txt_help.getGlobalBounds().height / 2.f);

	//carga texto game over
	this->txt_gameOver.setFont(this->txt_font);
	this->txt_gameOver.setCharacterSize(30);
	this->txt_gameOver.setFillColor(Color::Red);
	this->txt_gameOver.setString("Game Over!");
	this->txt_gameOver.setPosition(
		this->window->getSize().x / 2.f - this->txt_gameOver.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f - this->txt_gameOver.getGlobalBounds().height / 2.f);

	//carga texto genio
	this->txt_ganaste.setFont(this->txt_font);
	this->txt_ganaste.setCharacterSize(30);
	this->txt_ganaste.setFillColor(Color::Green);
	this->txt_ganaste.setString("Ganaste Genio");
	this->txt_ganaste.setPosition(
		this->window->getSize().x / 2.f - this->txt_ganaste.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 3.f - this->txt_ganaste.getGlobalBounds().height / 2.f);

	//carga texto play
	this->txt_play.setFont(this->txt_font);
	this->txt_play.setCharacterSize(30);
	this->txt_play.setFillColor(Color::White);
	this->txt_play.setString("clic P -> Play");
	this->txt_play.setPosition(
		this->window->getSize().x / 2.f - this->txt_play.getGlobalBounds().width / 2.f,
		this->window->getSize().y * 2.f / 3.f - this->txt_play.getGlobalBounds().height / 2.f);

	//carga texto quit
	this->txt_quit.setFont(this->txt_font);
	this->txt_quit.setCharacterSize(30);
	this->txt_quit.setFillColor(Color::White);
	this->txt_quit.setString("clic Q -> Quit");
	this->txt_quit.setPosition(
		this->window->getSize().x / 2.f - this->txt_play.getGlobalBounds().width / 2.f,
		this->window->getSize().y * 2.5f / 3.f - this->txt_play.getGlobalBounds().height / 3.f);
}
//inicia mundo
void Game::InitMundo()
{
	/*
		inicia fondo de pantalla
	*/
	if (!this->tex_mundo.loadFromFile("background.jpg"))
	{
		cout << "No se puede cargar background" << "\n";
	}

	this->spr_mundo.setTexture(this->tex_mundo);
}
//inicia variables
void Game::InitVariables()
{
	/*
		inicia variables
		- puntos del juego
		- dt = tiempo de generación de enemy
		- flags ganaste; gameover; menuActivo = controles del menú
		- reloj1 = contabiliza el tiempo de jeugo
	*/
	this->puntos = 0;
	this->dt = 1.f;
	this->ganaste = false;
	this->gameOver = false;
	this->menuActivo = true;
	this->reloj1 = new Clock();
}
//inicia Player
void Game::InitPlayer()
{
	this->player = new Player();
}
//inicia Enemy
void Game::InitEnemy()
{
	this->enemyTimerMax = 500.f;					//tiempo máximo entre generación de Enemy
	this->enemyTimer = this->enemyTimerMax;
}
//Constructor Game
Game::Game()
{
	/*
		inicia ventana
		inicia texturas
		inicia GUI
		inicia Mundo
		inicia variables
		inicia Player
		inicia Enemy
	*/
	this->InitWindow();
	this->InitTextures();
	this->InitSonidos();
	this->InitGUI();
	this->InitMundo();
	this->InitVariables();
	this->InitPlayer();
	this->InitEnemy();
}
//destructor
Game::~Game()
{
	delete this->window;
	delete this->player;
	
	//Delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto *i : this->bullets)
	{
		delete i;
	}

	//Delete enemy
	for (auto *i : this->enemy)
	{
		delete i;
	}
}
////loop de Game
void Game::LoopGame()
{
	/*
		mientras la ventana esté abierta, hacer:
		- escuchar eventos
		- si la vida del player es > 0 => actualiza Game
		- renderiza Game
	*/
	//dt = this->reloj1->restart().asSeconds();

	while (this->window->isOpen())
	{
		this->tiempo1 = this->reloj1->getElapsedTime();
		dt = this->tiempo1.asSeconds();

		this->PollEvents();

		if (gameOver == false && menuActivo == true)
		{
			RenderMenu();
		}
		
		if (gameOver == false && menuActivo == false && ganaste == false && this->player->getVida() > 0)
		{
			this->UpdateGame(dt);
			this->RenderGame();
		}
		
		if (ganaste == true)
		{
			this->RenderGanaste();
		}

		if (gameOver == true && menuActivo == true)
		{
			this->RenderGameOver();	
		}
		
		if (gameOver == true && menuActivo == false)
		{
			this->window->close();
			break;
		}

	
				
	}
}
//escucha eventos
void Game::PollEvents()
{
	/*
		mientras escuche type eventos en la ventana, hacer:
		- clic en tecla Escape => cierra la app
		- clic en cierre de ventana => cierra la app
	*/
	
	while (this->window->pollEvent(event))
	{
		
		if (event.Event::type == Event::Closed)
		{
			this->window->close();
			exit(1);
			break;
		}

		if (event.Event::KeyPressed && event.Event::key.code == Keyboard::Escape)
		{
			this->window->close();
			exit(1);
			break;
		}
		
		
		switch (event.key.code)
		{
				
		case Keyboard::P:
			this->menuActivo = false;
			this->gameOver = false;
			this->ganaste = false;
			break;
		
		case Keyboard::Q:
			this->gameOver = true; 
			this->menuActivo = false;
			break;
		}
	}
}
//actualiza la entrada de usuario
void Game::UpdateInput()
{
	/*
		si el evento es el movimiento del mouse => el player copia el movimeinto del mouse

		si clic en el boton Left del mouse => se crea un nuevo elemento en el último lugar del vector bullet con el valor del mapa ("BULLET",textura), 
		posición Player en x + ancho del player/2, posición Player en y, direción en x, dirección en y, velocidad
	*/
	
	this->player->setPosition((Vector2f)Mouse::getPosition(*window));
	
	
	switch (this->event.type)
	{
	case Event::MouseButtonPressed:
		if (event.mouseButton.button == Mouse::Button::Left && this->player->canAtaque())		//hace clic en botón izquierdo del mouse
		{
			//inicia el sonido de disparo
			this->sonidoDisparo.play();		//sonido de disparo
			//dispara bullet asignando la posición del bullet según posición del 
			float bulletSpeed = 5.f;	//define velocidad de cada bullet
			this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x + this->player->getBounds().width / 2.f, this->player->getPosition().y, 0.f, -1.f, bulletSpeed));
		}
	}
	
	
}
//actualiza GUI
void Game::UpdateGUI()
{
	/*
		define ss = cadena string
		construye ss = "Puntos" + puntos
		asigna al texto txt_puntos = string ss

		define vidaPorcentaje = vida/vidamax
		modifica al tamaño de playerBarraVida ( en x = 200 * vida porcentaje, en y = tamaño de la barra en y
	*/
	
	vidaPorcentaje = static_cast<float>(this->player->getVida()) / this->player->getVidaMax();
	
	stringstream ss;
	ss << "Puntos: " << this->puntos;
	this->txt_puntos.setString(ss.str());
	this->playerBarraVida.setSize(Vector2f(200.f * vidaPorcentaje, this->playerBarraVida.getSize().y));
	
}
//actualiza bullet
void Game::UpdateBullet()
{
	/*
	por cada bullet en el vector
		- actualiza la posición y velocidad de bullet
		- elimina bullet si toca top de pantalla (teniendo en cuenta la altura del sprite)
	*/
	unsigned bulletNumero = 0;
	for (auto *bullet : this->bullets)
	{
		bullet->Update_bullet();

		//elimina Bullet 
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(bulletNumero);
			this->bullets.erase(this->bullets.begin() + bulletNumero);
		}

		++bulletNumero;
	}
}
//actualiza enemy
void Game::UpdateEnemy(float _dt)
{
	/*
		incrementa enemyTimer en _dt
		si enemyTimer >= enemyTimerMax => crea un nuevo Enemy en x = posición aleatoria entre tamaño de pantalla - 20, en y en -100; enemyTimer = 0
	*/
	this->enemyTimer += _dt;
	
	if (this->enemyTimer >= this->enemyTimerMax)
	{
		this->enemy.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->enemyTimer = 0.f;
	}
	/*
		por fada enemy en el vector de objetos Enemy:
			- actualiza enemy
			- si el top del rectangulo del sprite enemy > tamaño de la ventana en y => delete el elemento enemy de vector [counter]
			limpia el último elemento del vector (equivalente al último elemento lo mueve hacia adelante)
			- si el enemy intercepta al player => vida del player se reduce según el daño del enemy (que depende del tipo de enemy); se delete
			el enemy que imactó; limpia el último elemento del vector (equivalente al último elemento lo mueve hacia adelante)
	*/
	unsigned counter = 0;
	for (auto *enemy : this->enemy)
	{
		enemy->UpdateEnemy();
		
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemy.at(counter);
			this->enemy.erase(this->enemy.begin() + counter);
		}
		//enemy colisiona con player
		else if(enemy->getBounds().intersects(this->player->getBounds()))
		{
			
			this->player->LoseVida(this->enemy.at(counter)->getDamage());
			delete this->enemy.at(counter);
			this->enemy.erase(this->enemy.begin() + counter);
		}
		if (this->player->getVida() <= 0)
		{
			gameOver = true;
			menuActivo = true;
			this->player->setVida(100);
			this->puntos = 0;
			
			for(unsigned int i = 0; i < (signed)this->enemy.size(); i++)
			{
				this->enemy.clear();
			}
			for (size_t k = 0; k < this->bullets.size() ; k++)
			{

				this->bullets.clear();
			}
			counter = 0;
		}
		++counter;
	}
}
//actualiza colisiones en combate
void Game::UpdateCollision()
{
	/*
		por cada enemy que queda vivo en el vector:
		- por cada bullet viva && no enemigo deleted:
			- si enemy intercepta a bullet => puntos = enemyCount; delete enemy; deleted el último del vector; 
	*/
	for (unsigned int i = 0; i < (signed) this->enemy.size(); i++)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemy[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->sonidoImpacto.play();
				this->puntos += this->enemy[i]->getPuntos();

				delete this->enemy[i];
				this->enemy.erase(this->enemy.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;

				if (this->puntos >= 1000)
				{
					this->ganaste = true;
					this->player->setVida(100);
					this->puntos = 0;

					for (unsigned int i = 0; i < (signed)this->enemy.size(); i++)
					{
						this->enemy.clear();
					}
					for (size_t k = 0; k < this->bullets.size() ; k++)
					{
						
						this->bullets.clear();
					}

					enemy_deleted = true;
				}
			}
		}
	}
}
//actualiza Game
void Game::UpdateGame(float _dt)
{
	/*
		actualiza inputs
		actualiza Player
		actualiza Bullet
		actualiza Enemy
		actualiza colisiones en combate
		actualiza GUI
	*/
	this->UpdateInput();

	this->player->UpdatePlayer();

	this->UpdateBullet();

	this->UpdateEnemy(dt);

	this->UpdateCollision();

	this->UpdateGUI();

}

//renderiza GUI
void Game::RenderGUI()
{
	/*
		renderiza texto puntos
		renderiza barra de vida del Player
	*/
	this->window->draw(this->txt_puntos);
	this->window->draw(this->playerBarraVidaBack);
	this->window->draw(this->playerBarraVida);
}
//renderiza Mundo
void Game::RenderMundo()
{
	this->window->draw(this->spr_mundo);
}
//renderiza Game
void Game::RenderGame()
{
	/*
		limpia ventana
		renderiza Mundo
		renderiza Player
		por cada bullet: renderiza bullet
		por cada enemy: renderiza enemy
		renderiza GUI
	*/
	this->window->clear();

	this->RenderMundo();

	this->player->RenderPlayer(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->RenderBullet(this->window);
	}

	for (auto* enemy : this->enemy)
	{
		enemy->RenderEnemy(this->window);
	}

	this->RenderGUI();
	
	
	this->window->display();
}
//renderiza menu
void Game::RenderMenu()
{
	
	this->RenderMundo();
	this->window->draw(this->txt_help);
	this->window->draw(this->txt_play);
	this->window->draw(this->txt_quit);
	this->window->display();
}
//rendiriza ganaste
void Game::RenderGanaste()
{
	this->window->clear();
	this->RenderMundo();
	this->window->draw(txt_ganaste);
	this->window->draw(this->txt_play);
	this->window->draw(this->txt_quit);
	this->window->display();
}
//renderiza game over
void Game::RenderGameOver()
{
	this->window->clear();
	this->RenderMundo();
	this->window->draw(this->txt_gameOver);
	this->window->draw(this->txt_play);
	this->window->draw(this->txt_quit);
	this->window->display();
}
