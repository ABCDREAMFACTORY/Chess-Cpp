#include "pieceManager.h"
#include <vector>

void PieceManager::setupPieces(Board& board) {
	// Initialize pieces on the board
	// This function can be implemented to set up pieces as needed
	board.reset();
}
bool PieceManager::movePiece(const Move& move, Board& board) {
	const Piece* pieceFrom = board.getPiece(move.getFrom());
	const Piece* pieceTo = board.getPiece(move.getTo());
	std::cout << "Recuperation of possibles moves" << std::endl;
	std::pair<bool, Move> moveInfo = this->isInPossibleMoves(move, pieceFrom->getPossibleMoves(move.getFrom(), board));
	std::cout << "En of recuperation of possibles moves" << std::endl;;
	if (moveInfo.first == false) {
		return false; // Move not valid
	}
	std::cout << "move found : " << moveInfo.second.getFrom().getX() << moveInfo.second.getFrom().getY() << moveInfo.second.getTo().getX() << moveInfo.second.getTo().getY() << std::endl;
	bool isCastling = moveInfo.second.isCastling();
	bool isEnPassant = moveInfo.second.isEnPassant();

	//make move
	board.movePiece(move);
	if (pieceFrom->getType() == Piece::PAWN && (move.getTo().getY() == 0 || move.getTo().getY() == 7)) {
		// Pawn promotion logic can be added here
		this->promotePawn(move.getTo(), pieceFrom->getColor(), board);
	}
	else if (isEnPassant) {
		// En passant capture logic
		Position capturedPawnPos(move.getTo().getX(), move.getFrom().getY());
		this->removePiece(capturedPawnPos, board);
	}
	else if (isCastling) {
		// Castling logic
		if (move.getTo().getX() == 6) { // King-side castling
			Move rookMove(Position(7, move.getFrom().getY()), Position(5, move.getFrom().getY()));
			board.movePiece(rookMove);
		}
		else if (move.getTo().getX() == 2) { // Queen-side castling
			Move rookMove(Position(0, move.getFrom().getY()), Position(3, move.getFrom().getY()));
			board.movePiece(rookMove);
		}
	}
	return true;
}
void PieceManager::removePiece(const Position& position, Board& board) {
	board.removePiece(position);
}
std::pair<bool,Move> PieceManager::isInPossibleMoves(const Move& move, const std::vector<Move>& possibleMoves) const {
	for (const auto& possibleMove : possibleMoves) {
		if (possibleMove.getFrom().getX() == move.getFrom().getX() &&
			possibleMove.getFrom().getY() == move.getFrom().getY() &&
			possibleMove.getTo().getX() == move.getTo().getX() &&
			possibleMove.getTo().getY() == move.getTo().getY()) {
			return std::make_pair(true, possibleMove);
		}
	}
	return std::make_pair(false,Move(-1,-1,-1,-1));
}

// Promotion d'un pion à la position donnée avec le choix spécifié
void PieceManager::promotePawn(Position pos, Piece::Color color, Board& board, char choice) {
	char c = std::toupper(static_cast<unsigned char>(choice));
	std::unique_ptr<Piece> newPiece;
	if (c == 'Q') newPiece = std::make_unique<Queen>(color);
	else if (c == 'R') newPiece = std::make_unique<Rook>(color);
	else if (c == 'B') newPiece = std::make_unique<Bishop>(color);
	else if (c == 'N') newPiece = std::make_unique<Knight>(color);
	else {
		// choix invalide : ne modifie pas le plateau (appelant peut gérer erreur)
		return;
	}
	board.changePiece(pos, std::move(newPiece));
}
// Promotion d'un pion à la position donnée en demandant à l'utilisateur
void PieceManager::promotePawn(Position pos, Piece::Color color, Board& board) {
	std::string input;
	while (true) {
		std::cout << "Promotion : choisissez (Q=Queen, R=Rook, B=Bishop, N=Knight) : ";
		if (!(std::cin >> input)) {
			// lecture échouée : clear et retry
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (input.empty()) continue;
		char c = input[0];
		promotePawn(pos, color, board, c); // réutilise la version testable
		break;
	}
}
void PieceManager::removeHasDoubleMovePawn(Piece::Color color, Board& board) {
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			Position pos(x, y);
			const Piece* piece = board.getPiece(pos);
			if (piece != nullptr && piece->getType() == Piece::PAWN && piece->getColor() == color) {
				Pawn* pawn = const_cast<Pawn*>(dynamic_cast<const Pawn*>(piece));
				if (pawn != nullptr) {
					pawn->hasDoubleMove = false;
				}
			}
		}
	}
}