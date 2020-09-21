#include "pch.h"
#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <cstdlib>

using namespace std;

bool gameOver;
int x, y, fruitX, fruitY, score; 
int tailX[684], tailY[684];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

char rozmiar, tryb, walls;
int width, height;

void Setup() {
	gameOver = false;
	dir = STOP;

	switch (rozmiar) {
	case '1': {
		width = 20;
		height = 20;
		break;
	}
	case '2': {
		width = 30;
		height = 20;
		break;
	}
	case '3': {
		width = 40;
		height = 20;
		break;
	}
	}

	x = width / 2;
	y = height / 2;
	srand(time(NULL));
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O"; //head
			else if (i == fruitY && j == fruitX)
				cout << "F";  //fruit
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o"; //tail
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	cout << "Wynik:" << score << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a': dir = LEFT; break;
		case 'd': dir = RIGHT; break;
		case 'w': dir = UP; break;
		case 's': dir = DOWN; break;
		case 'x': gameOver = true; break;
		}
	}

}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++; break;
	}


	if (x == fruitX && y == fruitY){
		score+=10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

	switch (walls) {
		case '1': {   //uderzenie to koniec gry

			if (x >= width || x < 0 || y >= height || y < 0)
				gameOver = true;

			break;
		}
		case '2': {  //przenikajace sciany

			if (x >= width) x = 0; else if (x <= 0) x = width;
			if (y >= height) y = 0; else if (y <= 0) y = height;

			break;
		}
	}
	
	for (int i = 0; i < nTail; i++) {  //uderzenie w ogon to koniec gry
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

}

int main()
{
	cout << "----------SNAKE GAME----------\n\n";
	cout << " Wybierz poziom trudnosci: \n";
	cout << " 1. EASY  2. MEDIUM  3. HARD \n\n";
	tryb = _getch();

	cout << " Wybierz rozmiar mapy: \n";
	cout << " 1. 20x20  2. 30x20  3. 40x20 \n\n";
	rozmiar = _getch();

	cout << " Wybierz rodzaj scian: \n";
	cout << " 1. STANDARD  2. PRZENIKAJACE \n\n";
	walls = _getch();

	Setup();
	while (!gameOver) {
		Draw();
		
		switch (tryb) {
			case '1': {  //easy
				if (dir == LEFT || dir == RIGHT)
				{
					Sleep(10);
				}

				Sleep(70);

				if (dir == UP || dir == DOWN)
				{
					Sleep(120);
				}
				break;
			}
			case '2': {  //medium
				if (dir == LEFT || dir == RIGHT)
				{
					Sleep(5);
				}

				Sleep(30);

				if (dir == UP || dir == DOWN)
				{
					Sleep(60);
				}
				break;
			}
			case '3': {  //hard
				if (dir == LEFT || dir == RIGHT)
				{
					Sleep(5);
				}

				if (dir == UP || dir == DOWN)
				{
					Sleep(60);
				}
				break;
			}

		}
	
		Input();
		Logic();
	}
	system("pause");
}