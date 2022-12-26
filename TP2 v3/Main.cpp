#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

using namespace std;


int main() {

	srand(static_cast<unsigned>(time(NULL)));
	
	Game* juego;
	juego = new Game();

	juego->LoopGame();
	
	return 0;
	}