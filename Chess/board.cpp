#include <vector>
#include "piece.h"
#include "board.h"

Board::Board() {
	Board::reset();
}

void Board::afficher() const {
	std::cout << "  a   b   c   d   e   f   g   h " << std::endl;
	int i = 1;
	for (const auto& row : pieces) {
		std::cout << i << " ";
		for (const auto& piecePtr : row) {
			if (piecePtr) {
				std::cout << *piecePtr << " ";
			}
			else {
				std::cout << " . ";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		i++;
	}
}

void Board::reset() {
	// crée un plateau 8x8 rempli de nullptr
	pieces.resize(8);
	for (auto& row : pieces) row.resize(8);

	// Rangée blanche (0) : tours, cavaliers, fous, dame, roi, fous, cavaliers, tours
	pieces[0][0] = std::make_unique<Rook>(Piece::WHITE);
	pieces[0][1] = std::make_unique<Knight>(Piece::WHITE);
	pieces[0][2] = std::make_unique<Bishop>(Piece::WHITE);
	pieces[0][3] = std::make_unique<King>(Piece::WHITE);
	pieces[0][4] = std::make_unique<Queen>(Piece::WHITE);
	pieces[0][5] = std::make_unique<Bishop>(Piece::WHITE);
	pieces[0][6] = std::make_unique<Knight>(Piece::WHITE);
	pieces[0][7] = std::make_unique<Rook>(Piece::WHITE);

	// Pions blancs (1)
	for (size_t i = 0; i < 8; ++i)
		pieces[1][i] = std::make_unique<Pawn>(Piece::WHITE);

	// Cases vides (2..5) déjà nullptr

	// Pions noirs (6)
	for (size_t i = 0; i < 8; ++i)
		pieces[6][i] = std::make_unique<Pawn>(Piece::BLACK);

	// Rangée noire (7) : mêmes pièces que la blanche mais en noir
	pieces[7][0] = std::make_unique<Rook>(Piece::BLACK);
	pieces[7][1] = std::make_unique<Knight>(Piece::BLACK);
	pieces[7][2] = std::make_unique<Bishop>(Piece::BLACK);
	pieces[7][3] = std::make_unique<King>(Piece::BLACK);
	pieces[7][4] = std::make_unique<Queen>(Piece::BLACK);
	pieces[7][5] = std::make_unique<Bishop>(Piece::BLACK);
	pieces[7][6] = std::make_unique<Knight>(Piece::BLACK);
	pieces[7][7] = std::make_unique<Rook>(Piece::BLACK);
}

bool Board::isInCheck(const Position& position , Piece::Color color) const {
	for (const std::vector<std::unique_ptr<Piece>>& row : pieces) {
		for (const std::unique_ptr<Piece>& piecePtr : row) {
			if (piecePtr && piecePtr->getColor() != color) {
				std::vector<Move> possibleMoves = piecePtr->getPossibleMoves(position, *this);
				for (const Move& move : possibleMoves) {
					if (move.getTo().getX() == position.getX() && move.getTo().getY() == position.getY()) {
						return true; // An opponent piece can attack the king
					}
				}
			}
		}
	}
	return false;
}