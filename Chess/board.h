#pragma once
#include <vector>
#include <memory>
#include "position.h"
#include "piece.h"
#include "move.h"


class Board {
public:
	Board();
	void afficher() const;
	void reset();
	void reset();
	const Piece*getPiece(Position pos) const {
		return pieces[pos.getY()][pos.getX()].get();
	}

	void changePiece(Position pos, std::unique_ptr<Piece> newPiece) {
		pieces[pos.getY()][pos.getX()] = std::move(newPiece);
	}
	void removePiece(Position pos) {
		pieces[pos.getY()][pos.getX()] = nullptr;
	}
	void movePiece(const Move& move) {
		pieces[move.getTo().getY()][move.getTo().getX()] = std::move(pieces[move.getFrom().getY()][move.getFrom().getX()]);
		this->removePiece(move.getFrom());
	}
	bool isInCheck(const Position& position, Piece::Color color) const;

private:
	std::vector<std::vector<std::unique_ptr<Piece>>> pieces;

};

