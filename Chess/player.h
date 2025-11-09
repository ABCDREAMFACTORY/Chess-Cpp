#pragma once

class Player {
public:
	Player(const char* name, bool isWhite) : playerName(name), white(isWhite) {}
	const char* getName() const { return playerName; }
	bool isWhiteSide() const { return white; }
private:
	const char* playerName;
	bool white;
};