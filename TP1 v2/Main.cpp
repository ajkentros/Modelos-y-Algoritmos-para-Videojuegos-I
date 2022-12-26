#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Juego.h"


using namespace sf;
using namespace std;

int main()
{
	srand(time_t(NULL));

	Juego* Juego1;

	Juego1 = new Juego();

	Juego1->Loop();



}