#pragma once
#include <iostream>
#include <string>

using namespace std;


class Units
{
public:
	Units(string Name, int Points, int Position);
	void Start(int x, int y, string Board[][8]);
	void Decision(int x, int y, string Board[][8]);
	void DecisionEnemy(int x, int y, string Board[][8]);
	bool AllCellsEmpty(int x, int y, string Board[][8]);
	bool AllCellsEmptyEnemy(int x, int y, string Board[][8]);
	int GetX(int x, int y, string Board[][8]);
	int GetXEnemy(int x, int y, string Board[][8]);
	int GetY(int x, int y, string Board[][8]);
	int GetYEnemy(int x, int y, string Board[][8]);
	void Movement(int x, int y, int z, int w, string Board[][8]);
	int CLength = 8;
	int CWidth = 8;
	string CName;
	int CPoints;
	int CPosition;
	int AttackPriority[4][4] =
	{
	{2,1,5,2},
	{2,2,1,5},
	{1,5,1,5},
	{2,2,2,2} };
	void AttackChoiceEnemy(int x, int y, string Board[][8]);
	void DoDamageEnemy(int x, int y, int Attack, string Board[][8]);
	void AttackChoice(int x, int y, string Board[][8]);
	void DoDamage(int x, int y, int Attack, string Board[][8]);
	int Convert(string Compare);
	void Reset();
	//void Heal(string Board[][8]);
	//void HealEnemy(string Board[][8]);

};