#include "Skill.h"

SkillClass::SkillClass()
{
}

SkillClass::~SkillClass()
{
}

void SkillClass::Wind(Game gplay, Player P1, Player P2)
{
	if (P1.MP < P1.MAXMP / 4)return;
	P1.MP -= P1.MAXMP / 4;

}
void SkillClass::Fire(Game gplay, Player P1, Player P2)
{
	if (P1.MP < P1.MAXMP / 4)return;
	P1.MP -= P1.MAXMP / 4;
	int x[5], y[5];
	for (int i = 0;i < 3;i++)
	{
		x[i] = rand() % (gplay.BFSize - 2) + 1;
		y[i] = rand() % (gplay.BFSize - 2) + 1;
		gplay.Tick[x[i]][y[i]] = gplay.BF[x[i]][y[i]];
		gplay.Tick[x[i]][y[i] + 1] = gplay.BF[x[i]][y[i] + 1];
		gplay.Tick[x[i]][y[i] - 1] = gplay.BF[x[i]][y[i] - 1];
		gplay.Tick[x[i] + 1][y[i]] = gplay.BF[x[i] + 1][y[i]];
		gplay.Tick[x[i] + 1][y[i] + 1] = gplay.BF[x[i] + 1][y[i] + 1];
		gplay.Tick[x[i] + 1][y[i] - 1] = gplay.BF[x[i] + 1][y[i] - 1];
		gplay.Tick[x[i] - 1][y[i]] = gplay.BF[x[i] - 1][y[i]];
		gplay.Tick[x[i] - 1][y[i] + 1] = gplay.BF[x[i] - 1][y[i] + 1];
		gplay.Tick[x[i] - 1][y[i] - 1] = gplay.BF[x[i] - 1][y[i] - 1];
	}
	P2.TakeDMG(10);
}
void SkillClass::Earth(Game gplay, Player P1, Player P2)
{
	if (P1.MP < P1.MAXMP / 4)return;
	P1.MP -= P1.MAXMP / 4;
	
}
void SkillClass::Water(Game gplay, Player P1, Player P2)
{
	if (P1.MP < P1.MAXMP / 4)return;
	P1.MP -= P1.MAXMP / 4;
	for(int i=0;i<gplay.BFSize;i++)
		for (int j = 0;j < gplay.BFSize;j++)
		{
			if (gplay.BF[i][j] == 3)
				gplay.Tick[i][j] = 3;
		}
	gplay.Turn += 2;
	P1.Healing(5);
	P2.TakeDMG(3);
}