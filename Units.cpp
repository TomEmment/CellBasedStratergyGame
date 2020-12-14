#include "Units.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdlib.h>



Units::Units(string Name, int Points, int Position)
{
	CName = Name;
	CPoints = Points;
	CPosition = Position;
	cout << Name <<" created" << endl;
}


void Units::Start(int x, int y, string Board[][8])
{
	if ((Board[x][y]).substr(0, 1) == "1")
	{
		Decision(x, y, Board);
	}
	if ((Board[x][y]).substr(0, 1) == "2")
	{
		DecisionEnemy(x, y, Board);
	}
}

void Units::Decision(int x, int y, string Board[][8])
{
	bool Decision;
	int z, w;
	Decision = AllCellsEmpty(x, y, Board);
	if (Decision == true)
	{
		z = GetX(x, y, Board);
		w = GetY(x, y, Board);
		Movement(x, y, z, w, Board);
		cout << endl << "Unit Moved" << endl;

	}
	if (Decision == false)
	{
		AttackChoice(x, y, Board);
	}
}

void Units::DecisionEnemy(int x, int y, string Board[][8])
{
	bool Decision;
	int z, w;
	Decision = AllCellsEmptyEnemy(x, y, Board);
	if (Decision == true)
	{
		z = GetXEnemy(x, y, Board);
		w = GetYEnemy(x, y, Board);
		Movement(x, y, z, w, Board);
	}
	if (Decision == false)
	{
		AttackChoiceEnemy(x, y, Board);

	}
}

bool Units::AllCellsEmpty(int x, int y, string Board[][8])
{
	bool InBoundX = true;
	bool InBoundX1 = true;
	bool InBoundY = true;
	bool InBoundY1 = true;
	bool Cell;
	if ((x + 1) > 7)
	{
		InBoundX = false;
	}
	if ((x - 1) < 0)
	{
		InBoundX1 = false;
	}
	if ((y + 1) > 7)
	{
		InBoundY = false;
	}
	if ((y - 1) < 0)
	{
		InBoundY1 = false;
	}

	if ((InBoundX == true) && ((Board[x + 1][y]).substr(0, 1) == "2"))
	{
		Cell = false;
	}
	else if ((InBoundX1 == true) && ((Board[x - 1][y]).substr(0, 1) == "2"))
	{
		Cell = false;
	}
	else if ((InBoundY == true) && ((Board[x][y + 1]).substr(0, 1) == "2"))
	{
		Cell = false;
	}
	else if ((InBoundY1 == true) &&((Board[x][y - 1]).substr(0, 1) == "2"))
	{
		Cell = false;
	}
	else
	{
		Cell = true;
	}
	return Cell;
}

bool Units::AllCellsEmptyEnemy(int x, int y, string Board[][8])
{
	bool InBoundX = true;
	bool InBoundX1 = true;
	bool InBoundY = true;
	bool InBoundY1 = true;
	bool Cell;
	if ((x + 1) > 7)
	{
		InBoundX = false;
	}
	if ((x - 1) < 0)
	{
		InBoundX1 = false;
	}
	if ((y + 1) > 7)
	{
		InBoundY = false;
	}
	if ((y - 1) < 0)
	{
		InBoundY1 = false;
	}

	if ((InBoundX == true) && ((Board[x + 1][y]).substr(0, 1) == "1"))
	{
		Cell = false;
	}
	else if ((InBoundX1 == true) && ((Board[x - 1][y]).substr(0, 1) == "1"))
	{
		Cell = false;
	}
	else if ((InBoundY == true) && ((Board[x][y + 1]).substr(0, 1) == "1"))
	{
		Cell = false;
	}
	else if ((InBoundY1 == true) && ((Board[x][y - 1]).substr(0, 1) == "1"))
	{
		Cell = false;
	}
	else
	{
		Cell = true;
	}
	return Cell;
}


int Units::GetX(int x, int y, string Board[][8])
{
	int Difference = 18;
	int temp, Cordinate;
	for (int z = 0; z < CWidth; z++)
	{
		for (int w = 0; w < CLength; w++)
		{
			if ((Board[z][w]).substr(0, 1) == "2")
			{
				temp = std::abs(z - x) + std::abs(w - y);
				if (temp < Difference)
				{
					Cordinate = z;
				}
			}
		}
	}
	return Cordinate;
}

int Units::GetXEnemy(int x, int y, string Board[][8])
{
	int Difference = 18;
	int temp, Cordinate;
	for (int z = 0; z < CWidth; z++)
	{
		for (int w = 0; w < CLength; w++)
		{
			if ((Board[z][w]).substr(0, 1) == "1")
			{
				temp = std::abs(x-z) + std::abs(y-w);
				if (temp < Difference)
				{
					Cordinate = z;
				}
			}
		}
	}
	return Cordinate;
}

int Units::GetY(int x, int y, string Board[][8])
{
	int Difference = 18;
	int temp, Cordinate;
	for (int z = 0; z < CWidth; z++)
	{
		for (int w = 0; w < CLength; w++)
		{
			if ((Board[z][w]).substr(0, 1) == "2")
			{
				temp = std::abs(z - x) + std::abs(w - y);
				if (temp < Difference)
				{
					Cordinate = w;
				}
			}
		}
	}
	return Cordinate;
}

int Units::GetYEnemy(int x, int y, string Board[][8])
{
	int Difference = 18;
	int temp, Cordinate;
	for (int z = 0; z < CWidth; z++)
	{
		for (int w = 0; w < CLength; w++)
		{
			if ((Board[z][w]).substr(0, 1) == "1")
			{
				temp = std::abs(z - x) + std::abs(w - y);
				if (temp < Difference)
				{
					Cordinate = w;
				}
			}
		}
	}
	return Cordinate;
}

void Units::Movement(int x, int y, int z, int w, string Board[][8])
{
	bool Swapped = false;
	while (Swapped == false)
	{
		if ((z > x)&& (Board[x + 1][y] == "0E00"))
		{
			Board[x + 1][y] = Board[x][y];
			Board[x][y] = "0E00";
			Swapped = true;
		}
		else if ((z < x) && (Board[x - 1][y] == "0E00"))
		{
			Board[x - 1][y] = Board[x][y];
			Board[x][y] = "0E00";
			Swapped = true;
		}
		else if ((y < w)&&(Board[x][y + 1] == "0E00"))
		{
				Board[x][y+1] = Board[x][y];
				Board[x][y] = "0E00";
				Swapped = true;
		}
		else if ((y > w) && (Board[x][y - 1] == "0E00"))
		{
				Board[x][y-1] = Board[x][y];
				Board[x][y] = "0E00";
				Swapped = true;
		}
		else
		{
			break;
		}
	}
}

void Units::AttackChoiceEnemy(int x, int y, string Board[][8])
{
	bool InBoundX = true;
	bool InBoundX1 = true;
	bool InBoundY = true;
	bool InBoundY1 = true;
	int Attack = 0;
	int temp;
	int CellX = x;
	int CellY = y;
	if ((x + 1) > 7)
	{
		InBoundX = false;
	}
	if ((x - 1) < 0)
	{
		InBoundX1 = false;
	}
	if ((y + 1) > 7)
	{
		InBoundY = false;
	}
	if ((y - 1) < 0)
	{
		InBoundY1 = false;
	}
	if ((InBoundX == true) && ((Board[x + 1][y]).substr(0, 1) == "1"))
	{
		temp = Convert((Board[x + 1][y]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellX = x + 1;
		}
	}
	if ((InBoundX1 == true) && ((Board[x - 1][y]).substr(0, 1) == "1"))
	{
		temp = Convert((Board[x - 1][y]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellX = x - 1;
		}
	}
	if ((InBoundY == true) && ((Board[x][y + 1]).substr(0, 1) == "1"))
	{
		temp = Convert((Board[x][y+1]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellY = y + 1;
			CellX = x;

		}
	}
	if ((InBoundY1 == true) && ((Board[x][y - 1]).substr(0, 1) == "1"))
	{
		temp = Convert((Board[x][y-1]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellY = y - 1;
			CellX = x;
		}
	}
	cout << endl << "Unit did " << Attack << " Damage."<<endl;
	DoDamageEnemy(CellX, CellY, Attack, Board);
}

int Units::Convert(string Compare )
{
	int Position, Attack;
	if (Compare == "I")
	{
		Position = 0;
	}
	if (Compare == "A")
	{
		Position = 1;
	}
	if (Compare == "C")
	{
		Position = 2;
	}
	if (Compare == "P")
	{
		Position = 3;
	}
	Attack = AttackPriority[CPosition][Position];
	return Attack;
}

void Units::DoDamageEnemy(int x, int y, int Attack, string Board[][8])
{
	string Cell;
	int n;
	Cell = Board[x][y];
	n = stoi((Board[x][y]).substr(2, 2));
	if ((n - Attack) <= 0)
	{
		Board[x][y] = "0E00";
	}
	else
	{
		if (n <= 9)
		{
			Board[x][y] = "1" + (Cell.substr(1,1)) + "0" + to_string(n);
		}
		else
		{
			Board[x][y] = "1" + (Cell.substr(1, 1)) + to_string(n);
		}
	}
}

void Units::DoDamage(int x, int y, int Attack, string Board[][8])
{
	string Cell;
	int n;
	Cell = Board[x][y];
	n = stoi((Board[x][y]).substr(2, 2));
	if ((n - Attack) <= 0)
	{
		Board[x][y] = "0E00";
	}
	else
	{
		n = n - Attack;
		if (n <= 9)
		{
			Board[x][y] = "2" + (Cell.substr(1, 1)) + "0" + to_string(n);
		}
		else
		{
			Board[x][y] = "2" + (Cell.substr(1, 1)) + to_string(n);
		}
	}
}

void Units::AttackChoice(int x, int y, string Board[][8])
{
	bool InBoundX = true;
	bool InBoundX1 = true;
	bool InBoundY = true;
	bool InBoundY1 = true;
	int Attack = 0;
	int temp;
	int CellX = x;
	int CellY = y;
	if ((x + 1) > 7)
	{
		InBoundX = false;
	}
	if ((x - 1) < 0)
	{
		InBoundX1 = false;
	}
	if ((y + 1) > 7)
	{
		InBoundY = false;
	}
	if ((y - 1) < 0)
	{
		InBoundY1 = false;
	}
	if ((InBoundX == true) && ((Board[x + 1][y]).substr(0, 1) == "2"))
	{
		temp = Convert((Board[x + 1][y]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellX = x + 1;
		}
	}
	if ((InBoundX1 == true) && ((Board[x - 1][y]).substr(0, 1) == "2"))
	{
		temp = Convert((Board[x - 1][y]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellX = x - 1;
		}
	}
	if ((InBoundY == true) && ((Board[x][y + 1]).substr(0, 1) == "2"))
	{
		temp = Convert((Board[x][y + 1]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellY = y + 1;
			CellX = x;

		}
	}
	if ((InBoundY1 == true) && ((Board[x][y - 1]).substr(0, 1) == "2"))
	{
		temp = Convert((Board[x][y - 1]).substr(1, 1));
		if (temp > Attack)
		{
			Attack = temp;
			CellY = y - 1;
			CellX = x;
		}
	}
	cout << endl << "Unit did " << Attack << " Damage." << endl;
	DoDamage(CellX, CellY, Attack, Board);
}
