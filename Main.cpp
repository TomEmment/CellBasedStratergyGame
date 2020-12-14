#include <iostream>
#include <string>
#include <fstream>
#include "Units.h"
#include "Infantry.h"
#include <Windows.h>


using namespace std;
int Length = 8;
int Width = 8;
int ArmyWidth = 3;
string Army[8][3];
Units Base("E", 0, 0);
Units Infantry("I",5,0);
Units Archer("A", 5, 1);
Units Cavelry("C", 10, 2);
Units Priest("P", 10, 3);
bool Moveable[8][8] = {
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,},
	{false,false,false,false,false,false,false,false,} };



void DisplayBoard(string Board[][8] ) {
	system("CLS");
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Length; y++)
		{
			cout << Board[x][y] << " ";
		}
		cout<<endl;
	}
	Sleep(0500);
}

bool IsCellEmpty(int x, int y) 
{
	bool Cell = false;
	if (Army[x][y] == "0E00")
	{
		Cell = true;
	}
	return Cell;
}


void DisplayArmy() {
	int Line = 0;
	cout << "       1    2    3    4    5    6    7    8  " << endl;
	for (int x = 0; x < ArmyWidth; x++)
	{
		for (int y = 0; y < Length; y++)
		{
			if (y == 0)
			{
				switch (Line)
				{
				case 0:
					cout << "  1  ";
					break;
				case 1:
					cout << "  2  ";
					break;
				case 2:
					cout << "  3  ";
					break;
				case 3:
					cout << "  4  ";
					break;
				case 4:
					cout << "  5  ";
					break;
				case 5:
					cout << "  6  ";
					break;
				case 6:
					cout << "  7  ";
					break;
				case 7:
					cout << "  8  ";
					break;

				}
			}
			cout << Army[y][x] << " ";
		}
		cout << endl;
		Line = Line + 1;

	}
}

void LoadArmy(string FileName) {
	ifstream armyFile(FileName);
	string Tile;
	for (int x = 0; x < Length; x++)
	{
		for (int y = 0; y < ArmyWidth; y++)
		{
			armyFile >> Tile;
			Army[x][y] = Tile;
		}
	}

}

void SaveArmy(string FileName)
{
	ofstream armyFile(FileName);
	for (int x = 0; x < Length; x++)
	{
		for (int y = 0; y < ArmyWidth; y++)
		{
			armyFile << Army[x][y] << endl;
		}
	}
}
int SelectTile(int max)
{
	int x;
	do {
		cout << "Please enter a cordiante between 1 and " << max << " ";
		cin >> x;
		cin.ignore();

	} while ((x < 1) || (x > max));
	x = x - 1;
	return x;

}

void UnitPoints(int Units = 3)
{
	while (Units > 0)
	{
		switch (Units)
		{
		case 1:
			cout << "Infantry costs " << Infantry.CPoints << " (1)" << endl;
		case 2:
			cout << "Archers costs " << Archer.CPoints << " (2)" << endl;
		case 3:
			cout << "Cavelry costs " << Cavelry.CPoints << " (3)" << endl;
		case 4:
			cout << "Priest costs " << Priest.CPoints << " (4)" << endl;
		}
		Units = Units - 1;
	}

}

int UnitCost(string Type)
{
	int temp;
	if (Type == "I")
	{
		temp = Infantry.CPoints;
	}
	if (Type == "A")
	{
		temp = Archer.CPoints;
	}
	if (Type == "C")
	{
		temp = Cavelry.CPoints;
	}
	if (Type == "P")
	{
		temp = Priest.CPoints;
	}
	return temp;
}

string UnitSelection(int max)
{
	int Choice;
	string Unit;
	do{
		cout << "Please Selected Your desired unit:" << endl;
		UnitPoints(1);
		cin >> Choice;
		switch (Choice)
		{
		case 1:
			Unit = "I";
			break;
		case 2:
			Unit = "A";
			break;
		case 3:
			Unit = "C";
			break;
		case 4:
			Unit = "P";
			break;
		}
	} while ((Choice < 1) || (Choice > max));
	return Unit;
}

int GetHealth()
{
	int Health;
	cout << "Enter Amount of health to be added: ";
	cin >> Health;
	return Health;

}



void CreateArmy(int Points)
{
	bool Empty;
	int x, y, Loss, w;
	string z, Name, Team;
	Team = "0";
	LoadArmy("Empty.txt");
	cout << "Is army Enemy(2) or Player(1)" << endl;
	cin >> Team;
	while (Points > 0)
	{
		Empty = false;
		system("CLS");
		DisplayArmy();
		cout << "You have " << Points << " remaining" << endl;
		do {
			x = SelectTile(8);
			y = SelectTile(3);
			Empty = IsCellEmpty(x, y);
			if (Empty == false)
			{
				cout << "Location occupied" << endl;
			}
		} while (Empty == false);
		z = UnitSelection(8);
		Loss = 100;
		do {
			w = GetHealth();
			Loss = w * UnitCost(z);
		} while ((Loss > Points) || (Loss < 1)||(w>99));
		Points = Points - Loss;
		Army[x][y] = Team + z + to_string(w);
	}
	cout << "Enter a name for your army" << endl;
	cin >> Name;
	Name = Name + ".txt";
	SaveArmy(Name);
	cout << "Army Saved";
}

void CreateInstance(string FileName, string FileNameEnemy, string Board[][8])
{
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Length; y++)
		{
			if ((x == 0)||(x==1)||(x==2))
			{
				LoadArmy(FileNameEnemy);
				Board[x][y] = Army[x][y];
			}
			if ((x == 5) || (x == 6) || (x == 7))
			{
				LoadArmy(FileName);
				Board[x][y] = Army[x-5][y];
			}
		}
	}
}

bool ArmiesUp(string Board[][8])
{
	bool XPresent = false;
	bool YPresent = false;
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Length; y++)
		{
			if ((Board[x][y]).substr(0, 1) == "1")
			{
				XPresent = true;
			}
			if ((Board[x][y]).substr(0, 1) == "2")
			{
				YPresent = true;
			}
		}

	}
	if ((XPresent = true) && (YPresent = true))
	{
		return true;
	}
	else if ((XPresent = true) && (YPresent = false))
	{
		cout << endl << "Player Wins!!!!!" << endl;
		return false;
	}
	else if ((XPresent = false) && (YPresent = true))
	{
		cout << endl << "AI Wins!!!!!" << endl;
		return false;
	}
	else
	{
		return false;
	}
}

void Fight(string Board[][8])
{
	DisplayBoard(Board);
	bool Present;
	Present = ArmiesUp(Board);
	while (Present == true)
	{
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Length; y++)
			{
				if ((Board[x][y]).substr(1, 1) != "E")
				{
					Moveable[x][y] = true;
				}
			}
		}
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Length; y++)
			{
				if (Present == false)
				{
					break;
				}
				if (((Board[x][y]).substr(1, 1) == "I")&&(Moveable[x][y] == true))
				{
					Infantry.Start(x, y, Board);
					DisplayBoard(Board);
				}
				else if (((Board[x][y]).substr(1, 1) == "A") && (Moveable[x][y] == true))
				{
					Archer.Start(x, y, Board);
					DisplayBoard(Board);
				}
				else if (((Board[x][y]).substr(1, 1) == "C") && (Moveable[x][y] == true))
				{
					Cavelry.Start(x, y, Board);
					DisplayBoard(Board);
				}
				else if (((Board[x][y]).substr(1, 1) == "P") && (Moveable[x][y] == true))
				{
					Priest.Start(x, y, Board);
					DisplayBoard(Board);
				}
				else
				{
					Present = ArmiesUp(Board);
					if (Present == false)
					{
						break;
					}
				}
				if (Present == false)
				{
					break;
				}
			}
			if (Present == false)
			{
				break;
			}

		}
		if (Present == false)
		{
			break;
		}
		for (int x = 0; x < Width; x++)
		{
			for (int y = 0; y < Length; y++)
			{
				Moveable[x][y] = false;
			}
		}
	}
}

void Menu(string Board[][8])
{
	string File1, File2;
	int x;
	int Points;
	x = 1;
	while (x != 0)
	{
		cout << "Welcome to the menu" << endl;
		cout << "Would you like to:" << endl;
		cout << "0 - Exit" << endl;
		cout << "1 - Create Army" << endl;
		cout << "2 - Choose two armies to fight:" << endl;
		cin >> x;
		if (x == 1)
		{
			cout << endl << "How many points would you like to have?"<<endl;
			cin >> Points;
			CreateArmy(Points);
		}
		if (x == 2)
		{
			cout << endl << "Select Hero file" << endl;
			cin >> File1;
			cout << endl << "Select Enemy file" << endl;
			cin >> File2;
			CreateInstance((File1+".txt"), (File2 +".txt"), Board);
			Fight(Board);
		}
	}
}

int main(){
	string EmptyBoard[8][8] = {
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",},
	{"0E00","0E00","0E00","0E00","0E00","0E00","0E00","0E00",} };
	Menu(EmptyBoard);
	cout << "Here";
	
	return 0;
}