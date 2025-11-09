#pragma once
#include "position.h"

class Move {

	public:
		Move(Position from, Position to) : from(from), to(to) {}
		Move(int fromX, int fromY, int toX, int toY) : from(fromX, fromY), to(toX, toY) {}
		Position getFrom() const { return from; }
		Position getTo() const { return to; }
		bool isCastling() const { return castling; }
		bool isEnPassant() const { return enPassant; }
		void setCastling(bool val) { castling = val; }
		void setEnPassant(bool val) { enPassant = val; }

	private:
		Position from;
		Position to;
		bool castling = false;
		bool enPassant = false;
};