#ifndef Player_h
#define Player_h
#include "Lib.h"

class Player
{
public:
	Player();
	~Player();
	int HP;
	int MP;
	int Food;
	int ATK;
	const int MAXHP = 1000;
	const int MAXMP = 1000;
	const int MAXFood = 1000;
	void TakeDMG(int amount);
	void Healing(int amount);
	void ManaRecovery(int amount);
	void Eat(int amount);
	void GatherFood(int amount);
};

#endif // !Player_h


