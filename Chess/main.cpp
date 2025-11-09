// Chess.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "chess.h"

int main()
{
	std::cout << "Chess program launched!\n";
	Chess chessGame;
	chessGame.runGameLoop();
	return 0;
}

