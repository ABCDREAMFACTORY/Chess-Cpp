#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "position.h"
class Board;
#include "move.h"

class Piece {
public:
	enum Type { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };
	enum Color { WHITE, BLACK };

	Piece(Type type, Color color);
	virtual ~Piece() = default;

	Type getType() const;
	Color getColor() const;
	char virtual get_symbol_piece() const;
	friend std::ostream& operator<<(std::ostream& os, const Piece& p);
	virtual std::vector<Move> getPossibleMoves(const Position& position ,const Board& board) const = 0; // To be implemented

protected:
	Type type;
	Color color;
};

class Rook : public Piece {
public:
	Rook(Color _color);

	char get_symbol_piece() const override;
	std::vector<Move> getPossibleMoves(const Position& position, const Board& board) const override;
	bool hasMoved = false;
};

class Knight : public Piece {
public:
	Knight(Color _color);
	char get_symbol_piece() const override;
	std::vector<Move> getPossibleMoves(const Position& position, const Board& board) const override;
};

class Bishop : public Piece {
public:
	Bishop(Color _color);
	char get_symbol_piece() const override;
	std::vector<Move> getPossibleMoves(const Position& position, const Board& board) const override;
};
class Queen : public Piece {
public:
	Queen(Color _color);
	char get_symbol_piece() const override;
	std::vector<Move> getPossibleMoves(const Position& position, const Board& board) const override;
};
class King : public Piece {
public:
	King(Color _color);
	char get_symbol_piece() const override;
	std::vector<Move> getPossibleMoves(const Position& position, const Board& board) const override;
	std::pair<Move, Move> getCastlingRookPosition(bool isKingSide , int posY) const;
	void getCastlingMoves(const Position& position, const Board& board, std::vector<Move>& possibleMoves) const;

	bool hasMoved = false;
};
class Pawn : public Piece {
public:
	Pawn(Color _color);
	char get_symbol_piece() const override;
	std::vector<Move> getPossibleMoves(const Position& position, const Board& board) const override;
	bool hasEnPassantMove = false;
};