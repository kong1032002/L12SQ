#ifndef SKILL_H
#define SKILL_H

#include "Lib.h"
#include "Game.h"
#include "Player.h"

class SkillClass
{
public:
	SkillClass();
	~SkillClass();
	void Fire(Game gplay, Player P1, Player P2);
	void Water(Game gplay, Player P1, Player P2);
	void Earth(Game gplay, Player P1, Player P2);
	void Wind(Game gplay, Player P1, Player P2);
};

#endif // !SKILL_H
