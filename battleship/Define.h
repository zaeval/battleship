#ifndef DEFINE_H
#define DEFINE_H

#define MAP_SIZE 8

#define SHIPS vector<Ship *>

#define ATTACKER_X 4
#define ATTACKER_Y 15
#define DEFENDER_X 4
#define DEFENDER_Y 4

#define IN
#define OUT

enum class DEFAULT_PALETTE{
	GREEN=1,
	CYAN,
	YELLOW,
	SEA,
	RED,
	SELECT
};
enum class HIT_RESULT {
	MISS = 'M',
	HIT = 'H',
	ALREADY_ATTACK,
	DESTROY ,
	GAME_CLEAR
};
enum class INSTANCE_TYPE {
	ATTACKER,
	DEFENDER
};
enum class GAME_MODE {
	PLAY_INPUT,
	PLAY_RANDOM,
	PLAY_FOLLOW_AI
};
enum class SHIP_TYPE {
	SHIP_NONE,
	AIRCRAFT='A',
	BATTLESHIP='B',
	CRUISER='C',
	DESTROYER='D',
	SHIP_CANT_PLACE
};
enum class SHIP_SIZE {
	DESTROYER=2,
	CRUISER,
	BATTLESHIP,
	AIRCRAFT,
};
enum class ROTATE_TYPE {
	HORIZONTAL,
	VERTICAL
};
struct Position {
	int x;
	int y;
	Position operator +(Position & p){
		return Position{ x + p.x, y + p.y };
	}
	Position operator -(Position &p) {
		return Position{ x - p.x,y - p.y };
	}
};
#endif