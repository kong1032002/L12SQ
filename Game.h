#pragma once
#ifndef Game_h
#define Game_h
#include "Lib.h"

class Game
{
public:
	Game();
	~Game();
	int Turn;
	int BFSize;
	int Combo;
	int BF[15][15];	// sàn đấu
	int Tick[15][15];
	int Act[15];
	bool CheckBF();
	void resetTick();
	int random();
};

#endif // !Game_h


