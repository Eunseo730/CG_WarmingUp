using namespace std;
#include <iostream>
#include <conio.h>
#define NOMINMAX
#include <windows.h>

struct Cell
{
	char value;
	bool isFind;
};

Cell board[6][6];
int score = 0;
int maxScore = 120;

int attempt = 20;

struct Pos
{
	int x;
	int y;

	bool operator==(const Pos& other) const 
	{
		return x == other.x && y == other.y;
	}

};

struct DoublePos
{
	Pos p1;
	Pos p2;

	bool operator==(const DoublePos& other) const 
	{
		return p1 == other.p1 && p2 == other.p2;
	}
};

DoublePos appear;

// 색상 설정 함수
void SetColor(int color) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearConsole()
{
	system("cls");  // 콘솔 화면 전체 지움
}

void Init()
{
	board[0][1].value = '1';
	board[0][2].value = '2';
	board[0][3].value = '3';
	board[0][4].value = '4';
	board[0][5].value = '5';

	board[1][0].value = '1';
	board[2][0].value = '2';
	board[3][0].value = '3';
	board[4][0].value = '4';
	board[5][0].value = '5';

	int countA = 0;
	int countB = 0;
	int countZ = 0;  // 조커
	int random;

	for (int j = 1; j < 6; j++)
	{
		for (int i = 1; i < 6; i++)
		{
			if (countZ < 1)
				random = rand() % 3;

			else
				random = rand() % 2;

			if (random == 2)
			{
				if (countZ >= 1)
				{
					i--;
					break;
				}

				else
				{
					board[j][i].value = 'Z';
					countZ++;
				}
			}

			else if (random == 0)
			{
				if (countA >= 12)
				{
					board[j][i].value = 'B';
					countB++;
				}

				else
				{
					board[j][i].value = 'A';
					countA++;
				}
			}

			else if (random == 1)
			{
				if (countB >= 12)
				{
					board[j][i].value = 'A';
					countA++;
				}

				else
				{
					board[j][i].value = 'B';
					countB++;
				}
			}
		}
	}
}

void Print()
{
	ClearConsole();

	for (int j = 0; j < 6; j++)
	{
		cout << endl;

		for (int i = 0; i < 6; i++)
		{
			if (board[j][i].value == 'A' || board[j][i].value == 'B' || board[j][i].value == 'Z')
				cout << "*" << "  ";
			else
			{
				cout << board[j][i].value << "  ";
			}
		}
		cout << endl;
	}
}

void Reset()
{
	score = 0;
	attempt = 20;

	Init();
	Print();
}

int GetDigit()
{
	while (true)
	{
		char ch = _getch();

		if (ch == 'r' || ch == 'R')
		{
			cout << "\nReset\n";
			Reset();
			return -1;  // 리셋 플래그
		}

		if (ch >= '1' && ch <= '5')
		{
			cout << ch << ' ';
			return ch - '0';
		}
	}
}

// 2개의 칸을 선택
DoublePos Choose()
{
	DoublePos choose;

	cout << "2개 칸 선택 (1~5, r: 리셋): ";

	int x1 = GetDigit(); if (x1 == -1) return Choose();
	int y1 = GetDigit(); if (y1 == -1) return Choose();
	int x2 = GetDigit(); if (x2 == -1) return Choose();
	int y2 = GetDigit(); if (y2 == -1) return Choose();

	choose.p1.x = x1;
	choose.p1.y = y1;
	choose.p2.x = x2;
	choose.p2.y = y2;

	cout << endl;

	char val1 = board[choose.p1.x][choose.p1.y].value;
	char val2 = board[choose.p2.x][choose.p2.y].value;

	if (((val1 == val2) || val1 == 'Z' || val2 == 'Z')
		&& !board[choose.p1.x][choose.p1.y].isFind
		&& !board[choose.p2.x][choose.p2.y].isFind)
	{
		board[choose.p1.x][choose.p1.y].isFind = true;
		board[choose.p2.x][choose.p2.y].isFind = true;

		score += 10;
	}

	attempt--;

	return choose;
}


void Print(DoublePos _appear)
{
	ClearConsole();

	for (int j = 0; j < 6; j++)
	{
		cout << endl;

		for (int i = 0; i < 6; i++)
		{
			char val = board[j][i].value;

			if (board[j][i].value == 'A' || board[j][i].value == 'B' || board[j][i].value == 'Z')
			{
				if ((j == _appear.p1.x && i == _appear.p1.y) ||
					(j == _appear.p2.x && i == _appear.p2.y) ||
					board[j][i].isFind == true)
				{
					if (val == 'A') SetColor(12);      // 빨강
					else if (val == 'B') SetColor(9);

					cout << board[j][i].value << "  ";
					SetColor(7);      // 복구
				}

				else
				{
					cout << "*" << "  ";
				}
			}

			else
			{
				cout << board[j][i].value << "  ";
			}
		}
		cout << endl;
	}

	cout << "score: " << score << endl;
	cout << "attempt: " << 20 - attempt << " / 20 " << endl;
}

int main()
{
	srand(unsigned(time(NULL)));

	Init();
	Print();

	while (true)
	{
		appear = Choose();
		Print(appear);

		if (score >= maxScore)
		{
			cout << "게임 승리!" << endl;
			return 0;
		}

		if (attempt <= 0)
		{
			cout << "시도 가능 횟수 끝..." << endl;
			return 0;
		}
	}
}

