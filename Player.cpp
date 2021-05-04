#include "Player.h"

Player::Player()
{
	HP = MAXHP;
	MP = MAXMP;
	Food = MAXFood;
	ATK = 100;
}

Player::~Player()
{
	HP = MAXHP;
	MP = MAXMP;
	Food = MAXFood;
	ATK = 100;
}

void Player::Eat(int amount)
{
	Food = max(Food - amount * 10, 0);
}

void Player::GatherFood(int amount)
{
	Food = min(Food + amount * 10, MAXFood);
}

void Player::Healing(int amount)
{
	HP = min(HP + amount * ATK, MAXHP);
}

void Player::TakeDMG(int amount)
{
	HP = max(HP - amount * ATK, 0);
}

void Player::ManaRecovery(int amount)
{
	MP = min(MP + amount * 10, MAXMP);
}