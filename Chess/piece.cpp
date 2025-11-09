#include "piece.h"
#include "board.h"

//piece implementation
Piece::Piece(Piece::Type type, Piece::Color color)
	: type(type), color(color) {}
Piece::Type Piece::getType() const { return type; }
Piece::Color Piece::getColor() const { return color; }
char Piece::get_symbol_piece() const { return '?'; }
std::ostream& operator<<(std::ostream& os, const Piece& p) {
	os << p.get_symbol_piece();
	switch (p.color) {
	case Piece::Color::WHITE:
		os << "w"; break;
	case Piece::Color::BLACK:
		os << "b"; break;
	}
	return os;
}

//rook implementation
Rook::Rook(Piece::Color _color) : Piece(Piece::ROOK, _color) {}
char Rook::get_symbol_piece() const { return 'r'; }
std::vector<Move> Rook::getPossibleMoves(const Position& position,const Board& board) const {
	// To be implemented
	std::vector<Move> possibleMoves;
	const Piece* pieceAtPos = board.getPiece(position);
	std::vector<std::pair<int, int>> directions = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	for (std::pair<int,int>& dir : directions) {
		int x = position.getX();
		int y = position.getY();
		while (true) {
			x += dir.first;
			y += dir.second;
			if (x < 0 || x >= 8 || y < 0 || y >= 8) break; // Out of bounds
			Position newPos(x, y);
			const Piece* pieceAtNewPos = board.getPiece(newPos);
			if (pieceAtNewPos == nullptr) {
				possibleMoves.push_back(Move(position, newPos));
			}
			else {
				if (pieceAtNewPos->getColor() != this->getColor()) {
					possibleMoves.push_back(Move(position, newPos)); // Capture
				}
				break; // Blocked by a piece
			}
		}
	}
	return possibleMoves;
}

//knight implementation
Knight::Knight(Piece::Color _color) : Piece(Piece::KNIGHT, _color) {}
char Knight::get_symbol_piece() const { return 'n'; }
std::vector<Move> Knight::getPossibleMoves(const Position& position, const Board& board) const {
	std::vector<Move> possibleMoves;
	std::vector<std::pair<int, int>> knightMoves = {
		{2, 1}, {1, 2}, {-1, 2}, {-2, 1},
		{-2, -1}, {-1, -2}, {1, -2}, {2, -1}
	};
	for (std::pair<int,int> move : knightMoves) {
		int newX = position.getX() + move.first;
		int newY = position.getY() + move.second;
		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
			Position newPos(newX, newY);
			const Piece* pieceAtNewPos = board.getPiece(newPos);
			if (pieceAtNewPos == nullptr || pieceAtNewPos->getColor() != this->getColor()) {
				possibleMoves.push_back(Move(position, newPos));
			}
		}
	}

	return possibleMoves;
}

//bishop implementation
Bishop::Bishop(Piece::Color _color) : Piece(Piece::BISHOP, _color) {}
char Bishop::get_symbol_piece() const { return 'b'; }
std::vector<Move> Bishop::getPossibleMoves(const Position& position, const Board& board) const {
	std::vector<Move> possibleMoves;
	std::vector<std::pair<int, int>> directions = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };
	for (std::pair<int, int>& dir : directions) {
		int newX = position.getX(), newY = position.getY();
		while (true) {
			newX = newX + dir.first;
			newY = newY + dir.second;
			if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) break; // Out of bounds
			const Piece* pieceAtNewPos = board.getPiece(Position(newX, newY));
			if (pieceAtNewPos == nullptr) {
				possibleMoves.push_back(Move(position, Position(newX, newY)));
			}
			else {
				if (pieceAtNewPos->getColor() != this->getColor()) {
					possibleMoves.push_back(Move(position, Position(newX, newY))); // Capture
				}
				break; // Blocked by a piece
			}
		}
	}
	return possibleMoves;
}

//queen implementation
Queen::Queen(Piece::Color _color) : Piece(Piece::QUEEN, _color) {}
char Queen::get_symbol_piece() const { return 'q'; }
std::vector<Move> Queen::getPossibleMoves(const Position& position, const Board& board) const {
	std::vector<Move> possibleMoves;
	// Combine Rook and Bishop moves
	Rook rookPart(this->getColor());
	Bishop bishopPart(this->getColor());
	std::vector<Move> rookMoves = rookPart.getPossibleMoves(position, board);
	std::vector<Move> bishopMoves = bishopPart.getPossibleMoves(position, board);
	possibleMoves.insert(possibleMoves.end(), rookMoves.begin(), rookMoves.end());
	possibleMoves.insert(possibleMoves.end(), bishopMoves.begin(), bishopMoves.end());
	return possibleMoves;
}

//king implementation
King::King(Piece::Color _color) : Piece(Piece::KING, _color) {}
char King::get_symbol_piece() const { return 'k'; }
std::vector<Move> King::getPossibleMoves(const Position& position, const Board& board) const {
	std::vector<Move> possibleMoves;
	std::vector<std::pair<int, int>> kingMoves = { 
		{1, 0}, {1, 1}, {0, 1}, {-1, 1},
		{-1, 0}, {-1, -1}, {0, -1}, {1, -1}
	};
	for (std::pair<int, int> move : kingMoves) {
		int newX = position.getX() + move.first;
		int newY = position.getY() + move.second;
		if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
			Position newPos(newX, newY);
			const Piece* pieceAtNewPos = board.getPiece(newPos);
			if (pieceAtNewPos == nullptr || pieceAtNewPos->getColor() != this->getColor()) {
				possibleMoves.push_back(Move(position, newPos));
			}
		}
	}
	// Castling
	if (!hasMoved) {
		getCastlingMoves(position, board, possibleMoves);
	}

	return possibleMoves;
}
std::pair<Move, Move> King::getCastlingRookPosition(bool isKingSide , int posY) const {
	std::pair<Move, Move> moves = { Move(Position(7, posY), Position(5, posY)), Move(Position(7, posY), Position(5, posY)) };
	return moves;
}
void King::getCastlingMoves(const Position& position, const Board& board, std::vector<Move>& possibleMoves) const {
	std::pair<Move, Move> castlingMoves = getCastlingRookPosition(true, position.getY());
	Move movesArray[2] = { castlingMoves.first, castlingMoves.second };
	for (const Move& move : movesArray) {
		const Piece* pieceAtRookPos = board.getPiece(move.getFrom());
		if (pieceAtRookPos == nullptr || pieceAtRookPos->getType() == Piece::ROOK) continue;
		const Rook* rook = const_cast<Rook*>(dynamic_cast<const Rook*>(pieceAtRookPos));
		if (rook->hasMoved || board.isInCheck(Position(move.getFrom().getX(), position.getY()), this->getColor())) continue;
		// Check if squares between king and rook are empty
		int step = (move.getFrom().getX() > position.getX()) ? 1 : -1;
		for (int x = position.getX() + step; x != move.getFrom().getX(); x += step) {
			if (board.getPiece(Position(x, position.getY())) != nullptr) {
				continue;
			}
			else if (board.isInCheck(Position(x, position.getY()), this->getColor())) {
				continue;
			} else {
				// Valid castling move
				Move kingMove(position, Position(position.getX() + 2 * step, position.getY()));
				kingMove.setCastling(true);
				possibleMoves.push_back(kingMove);
			}
		}
	}
}


//pawn implementation
Pawn::Pawn(Piece::Color _color) : Piece(Piece::PAWN, _color) {}
char Pawn::get_symbol_piece() const { return 'p'; }
std::vector<Move> Pawn::getPossibleMoves(const Position& position, const Board& board) const {
	std::vector<Move> possibleMoves;
	int direction = (this->getColor() == Piece::WHITE) ? 1 : -1;
	int startRow = (this->getColor() == Piece::WHITE) ? 1 : 6;
	// Move forward
	Position oneStepForward(position.getX(), position.getY() + direction);
	if (board.getPiece(oneStepForward) == nullptr) {
		possibleMoves.push_back(Move(position, oneStepForward));
		// First move can be two steps
		if (position.getY() == startRow) {
			Position twoStepsForward(position.getX(), position.getY() + direction*2);
			if (board.getPiece(twoStepsForward) == nullptr) {
				possibleMoves.push_back(Move(position, twoStepsForward));
			}
		}
	}
	// Captures
	Position captureLeft(position.getX() - 1, position.getY() + direction);
	Position captureLeftEnPassant(position.getX() - 1, position.getY());
	Position captureRight(position.getX() + 1, position.getY() + direction);
	Position captureRightEnPassant(position.getX() + 1, position.getY());
	const Piece* pieceAtLeft = board.getPiece(captureLeft);
	const Piece* pieceAtLeftEnPassant = board.getPiece(captureLeftEnPassant);
	const Piece* pieceAtRight = board.getPiece(captureRight);
	const Piece* pieceAtRightEnPassant = board.getPiece(captureRightEnPassant);
	if (pieceAtLeft != nullptr && pieceAtLeft->getColor() != this->getColor()) {
		possibleMoves.push_back(Move(position, captureLeft));
	}
	else if (pieceAtLeftEnPassant != nullptr && pieceAtLeftEnPassant->getType() == Piece::PAWN && pieceAtLeftEnPassant->getColor() != this->getColor()){
		possibleMoves.push_back(Move(position, captureLeftEnPassant));
		possibleMoves.back().setEnPassant(true);
	}
	if (pieceAtRight != nullptr && pieceAtRight->getColor() != this->getColor()) {
		possibleMoves.push_back(Move(position, captureRight));
	}
	else if (pieceAtRightEnPassant != nullptr && pieceAtRightEnPassant->getType() == Piece::PAWN && pieceAtRightEnPassant->getColor() != this->getColor()) {
		possibleMoves.push_back(Move(position, captureRightEnPassant));
		possibleMoves.back().setEnPassant(true);
	}
	return possibleMoves;
}