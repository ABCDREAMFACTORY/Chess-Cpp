#pragma once
#include <vector>
#include "piece.h"
#include "position.h"
#include "board.h"
class PieceManager {

	public:
	static PieceManager& getInstance() {
		static PieceManager instance;
		return instance;
	}
	// Delete copy constructor and assignment operator to prevent copies
	PieceManager(const PieceManager&) = delete;
	PieceManager& operator=(const PieceManager&) = delete;
	// Add methods to manage pieces if needed
	void setupPieces(Board& board);
	bool movePiece(const Move& move , Board& board);
	void removePiece(const Position& position , Board& board);
	std::pair<bool,Move> isInPossibleMoves(const Move& move, const std::vector<Move>& possibleMoves) const;
	void promotePawn(Position pos, Piece::Color color, Board& board);
	void promotePawn(Position pos, Piece::Color color, Board& board, char choice);




private:
	PieceManager() {} // Private constructor for singleton
	~PieceManager() {}
	// Add member variables to manage pieces if needed
	enum typePromotion { QUEEN, ROOK, BISHOP, KNIGHT };
	static const char* typePromotionToString(typePromotion t) {
		switch (t) {
		case QUEEN: return "QUEEN";
		case ROOK:  return "ROOK";
		case BISHOP:return "BISHOP";
		case KNIGHT:return "KNIGHT";
		default:    return "UNKNOWN";
		}
	}
};
