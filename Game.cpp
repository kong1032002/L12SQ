#include "Game.h"

Game::Game()
{
	Combo = 1;
	srand(time(NULL));
	BFSize = 8;
	for (int i = 0;i < BFSize;i++)
	{
		Act[i] = 0;
		for (int j = 0;j < BFSize;j++)
		{
			Tick[i][j] = 0;
			BF[i][j] = random();
		}
	}
	Turn = 1;
	while (CheckBF())
	{
		for (int j = 0;j < BFSize;j++)
		for (int i = 0;i < BFSize;i++)
			if (BF[i][j] == 0)
			for (int k = i;k >= 0;k--)
			{
				if (k == 0)
					BF[k][j] = random();
				else
					swap(BF[k - 1][j], BF[k][j]);
			}
	}
}

Game::~Game()
{
	Turn = 1;
}

int Game::random()
{
	int temp = rand() % 14 + 2;
	return temp / 2;
}

void Game::resetTick()
{
	Combo = 1;
	for (int i = 0;i < BFSize;i++)
	for (int j = 0;j < BFSize;j++)
	{
		if (Tick[i][j] != 0)
		{
			Act[BF[i][j]]+=Combo;
			Tick[i][j] = 0;
			if (BF[i][j] == 7)
			{
				BF[i + 1][j] = 0;			Act[BF[i + 1][j]] += Combo;
				BF[i][j + 1] = 0;			Act[BF[i][j + 1]] += Combo;
				BF[i + 1][j + 1] = 0;		Act[BF[i + 1][j + 1]] += Combo;
				if (j - 1 >= 0)
				{
					BF[i][j - 1] = 0;			Act[BF[i][j - 1]] += Combo;
					BF[i + 1][j - 1] = 0;		Act[BF[i + 1][j - 1]] += Combo;
				}
				if (i - 1 >= 0)
				{
					BF[i - 1][j] = 0;		Act[BF[i - 1][j]] += Combo;
					BF[i - 1][j + 1] = 0;	Act[BF[i - 1][j + 1]] += Combo;		
				}
				if (i - 1 >= 0 && j - 1 >= 0)
					BF[i - 1][j - 1] = 0;	Act[BF[i - 1][j] - 1] += Combo;
			}
			BF[i][j] = 0;
		}
	}
}

bool Game::CheckBF()
{
	bool flag = 0;
	for (int i = 0;i < BFSize;i++)
	for (int j = 0;j < BFSize;j++)
	{
		if (BF[i][j] != 0)
		{
			if (BF[i][j] == BF[i + 1][j] && BF[i][j]== BF[i+2][j])
			{
				flag = 1;
				Tick[i][j] = BF[i][j];
				Tick[i + 1][j] = BF[i][j];
				Tick[i + 2][j] = BF[i][j];
				if (BF[i][j] == BF[i + 3][j])
				{
					Turn++;
					Tick[i + 3][j] = BF[i][j];
					if (BF[i][j] == BF[i + 4][j])
						Tick[i + 4][j] = BF[i][j];
				}
			}
			if (BF[i][j] == BF[i][j+1] && BF[i][j] == BF[i][j+2])
			{
				flag = 1;
				Tick[i][j] = BF[i][j];
				Tick[i][j + 1] = BF[i][j];
				Tick[i][j + 2] = BF[i][j];
				if (BF[i][j] == BF[i][j+3])
				{
					Turn++;
					Tick[i][j + 3] = BF[i][j];
					if (BF[i][j] == BF[i][j + 4])
						Tick[i][j + 4] = BF[i][j];
				}
			}
		}
	}
	resetTick();
	return flag;
}