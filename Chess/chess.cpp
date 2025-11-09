#include "chess.h"
#include "board.h"

static bool parseSquare(const std::string& s, Position& pos) {
	if (s.size() != 2) return false;
	char file = static_cast<char>(std::tolower(s[0]));
	char rank = s[1];
	if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return false;
	int x = file - 'a';
	int y = rank - '1';
	std::cout << "Parsed square: " << s << " to position (" << x << ", " << y << ")" << std::endl;
	pos = Position(x, y);
	return true;
}

Chess::Chess() {
	// Constructor implementation (if needed)
}

void Chess::startGame() {
	chessBoard.reset();
	chessBoard.afficher();
}

void Chess::updateGame() {
	// Game update logic (to be implemented)
	pieceManager.removeHasDoubleMovePawn(currentPlayer->isWhiteSide() ? Piece::WHITE : Piece::BLACK, chessBoard);
	do {
		if (tryMove()) {
			break; // Exit loop if move was successful
		}
	} while (true); // Loop until a valid move is made
	
	chessBoard.afficher();
}

void Chess::endGame() {
	// Game end logic (to be implemented)
}

void Chess::runGameLoop() {
	startGame();
	while (winner == nullptr) {
		updateGame();
		// Check for checkmate, stalemate, etc. to set winner
	}
	endGame();
}

bool Chess::tryMove() {
	std::string fromStr, toStr;
	Position fromPos, toPos;
	std::cout << currentPlayer->getName() << "'s turn. Enter your move (e.g., e2 e4): ";
	std::cin >> fromStr >> toStr;
	if (!parseSquare(fromStr, fromPos) || !parseSquare(toStr, toPos)) {
		std::cout << "Invalid input format. Please use the format 'e2 e4'." << std::endl;
		return false;
	}
	Move move(fromPos, toPos);
	const Piece* p = chessBoard.getPiece(fromPos);
	if (!p) {
		std::cout << "No piece at " << fromStr << " — choose a non-empty square.\n";
		return false;
	} else if (p->getColor() == Piece::WHITE && !currentPlayer->isWhiteSide()) {
		std::cout << "That's not your piece! It's Black to move.\n";
		return false;
	} else if (p->getColor() == Piece::BLACK && currentPlayer->isWhiteSide()) {
		std::cout << "That's not your piece! It's White to move.\n";
		return false;
	}
	if (pieceManager.movePiece(move, chessBoard)) {
		// Move successful
		std::cout << "move has been successfull\n";
		if (Piece::Type::KING == p->getType()) {
			King* king = dynamic_cast<King*>(const_cast<Piece*>(p));
			king->setHasMoved(true);
		} else if (Piece::Type::ROOK == p->getType()) {
			Rook* rook = dynamic_cast<Rook*>(const_cast<Piece*>(p));
			rook->setHasMoved(true);
		} else if (Piece::Type::PAWN == p->getType() && (move.getFrom().getY() - move.getTo().getY() == 2 || move.getTo().getY() - move.getFrom().getY() == 2)) {
			Pawn* pawn = dynamic_cast<Pawn*>(const_cast<Piece*>(p));
			pawn->setHasDoubleMove(true);
		}
		currentPlayer = (currentPlayer == &whitePlayer) ? &blackPlayer : &whitePlayer;
		return true;
	} else {
		std::cout << "Invalid move. Try again." << std::endl;
		return false;
	}
}