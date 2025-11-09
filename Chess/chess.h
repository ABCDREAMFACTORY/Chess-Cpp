#pragma once
#include "board.h"
#include "move.h"
#include "pieceManager.h"
#include "player.h"
class Chess {
public:
	Chess();
	void startGame();
	void updateGame();
	void endGame();
	void runGameLoop();
	void displayBoard() {chessBoard.afficher();}
	void resetBoard() { chessBoard.reset(); }
	bool tryMove();
private:
	Board chessBoard;
	PieceManager& pieceManager = PieceManager::getInstance();
	Player whitePlayer{ "White", true };
	Player blackPlayer{ "Black", false };
	Player* currentPlayer = &whitePlayer;
	Player* winner = nullptr;
};