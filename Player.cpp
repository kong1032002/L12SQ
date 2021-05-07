#include "Player.h"

Player::Player()
{
	HP = MAXHP;
	MP = MAXMP;
	Food = MAXFood;
	EXP = 0;
	ATK = 7;
	Level = 1;
}

Player::~Player()
{
	HP = MAXHP;
	MP = MAXMP;
	Food = MAXFood;
	ATK = 7;
	EXP = 0;
	Level = 1;
}

void Player::Eat()
{
	Food = max(Food - 1, 0);
}

void Player::GatherFood(int amount)
{
	Food = min(Food + amount * 5, MAXFood);
}

void Player::Healing(int amount)
{
	HP = min(HP + amount * 5, MAXHP);
}

void Player::TakeDMG(int amount)
{
	HP = max(HP - amount * ATK, 0);
}

void Player::ManaRecovery(int amount)
{
	MP = min(MP + amount * 5, MAXMP);
}

void Player::GetExp(int amount)
{
	EXP += amount;
	if (EXP >= MAXEXP)
	{
		Level++;
		ATK += 2;
		EXP -= MAXEXP;
	}
}