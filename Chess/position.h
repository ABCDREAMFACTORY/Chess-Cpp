#pragma once

class Position {
	public:
		Position(int x = 0, int y = 0) : xCoord(x), yCoord(y) {}
		int getX() const { return xCoord; }
		int getY() const { return yCoord; }
		void setX(int x) { xCoord = x; }
		void setY(int y) { yCoord = y; }
	private:
		int xCoord;
		int yCoord;
};