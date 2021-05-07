#ifndef Player_h
#define Player_h
#include "Lib.h"
#include "Game.h"

class Player
{
public:
	Player();
	~Player();
	int HP;
	int MP;
	int Food;
	int ATK;
	int EXP;
	int Level;
	void GetExp(int amount);
	void TakeDMG(int amount);
	void Healing(int amount);
	void ManaRecovery(int amount);
	void Eat();
	void GatherFood(int amount);
	const int MAXEXP = 50;
	const int MAXHP = 200;
	const int MAXMP = 100;
	const int MAXFood = 500;
};

#endif // !Player_h


