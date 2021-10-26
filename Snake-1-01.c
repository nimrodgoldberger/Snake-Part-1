//Nimrod Goldberger I.D:316169036
//this program is a game of snake only the first difficulty level was required for this project, at the moment.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#define UP 72  // Up Arrow 
#define DOWN 80 // Down Arrow 
#define LEFT 75  // Left Arrow 
#define RIGHT 77  // Right Arrow 
#define ESC 27  // Escape Key
#define ROWS 25//the height of the board
#define COLS 75//the width of the board
#define MAXSNAKESIZE 20//when the snake reaches this size, the game is won

typedef struct Block
{
	int X;
	int Y;
} block;//this struct keeps the coordinates of objects: fruits and snake parts

void endgame(bool status);// the function that prints the you win or, you lose messages, depending on the situation
void spreadfruit(block*snake, int snakelength, block* fruit);//randomally spawns a $ which is a 'fruit', across the board
void printsnake(block* snake, int snakelength, int x, int y);//erases the 'tail' of the snake, gives every part of the snake the coordination of the one closer to the head, and prints the head in the new location
void updateSnake(block* snake, int snakelength, int x, int y);//in the start of the game, places the 10 parts of the snake in the same coordination, just for the beginning
void gameBoard();//prints the frame of the game
int printmenu();//prints the options menu, and returns the choice as an integer
void lineofstars();//prints a line of '*' for the menu
void gotoxy(int y, int x);
int getKey();
void checkAlloc(block* snake);//checks if the allocation was successful
bool isquitting(bool PLAYING, int* choice);//runs the program until the player decides to quit, even if he loses
bool rungame(int* choice);//this function runs the game itself
block* reallocate(block* snake, int snakelength);//reallocates the struct array of the snake with the new size after eating a fruit

//MAIN PROGRAM
void main()
{
	srand(time(NULL));//to randommally spawn a fruit
	gotoxy(0, 0);
	int* choice;
	bool PLAYING = true;
	while (PLAYING == true)//until the player quits
	{
		choice = printmenu();
		system("cls");
		if (choice != 0)
		{
			PLAYING = isquitting(PLAYING, &choice);
		}
		else
		{
			PLAYING = false;
		}
	}
	system("cls");
	printf("\n\n\n                      Goodbye. Thanks for Playing!                      \n\n");
}

//Functions:
void gotoxy(int y, int x) {
	printf("\x1b[%d;%df", x + 1, y + 1);
}

int getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}

int printmenu()
{
	int choice;
	lineofstars();
	printf("*Pick your Level, for exit press 0\n");
	printf("* 0 -Exit\n");
	printf("* 1 - Basic Level\n");
	printf("* 2 - Intermidiate LEvel\n");
	printf("* 3 - Advanced Level\n");
	lineofstars();
	scanf("  %d", &choice);
	return choice;
}

void lineofstars()
{
	for (int i = 0; i < 70; i++)
	{
		printf("*");
	}
	printf("\n");
}

void checkAlloc(block* snake)
{
	if (snake == NULL)
	{
		printf("\n\nThe Allocation Was Not Successful, The Programm Will Now Close...\n\n");
		exit(0);
	}
}

void updateSnake(block* snake, int snakelength, int x, int y)
{
	int i;
	for (i = 0; i < snakelength; i++)
	{
		(snake + i)->X = x;
		(snake + i)->Y = y;
	}
}

void printsnake(block* snake, int snakelength, int x, int y)
{
	gotoxy(snake[snakelength - 1].X, snake[snakelength - 1].Y);
	printf(" ");
	int i;
	for (i = snakelength - 1; i > 0; i--)
	{
		snake[i].X = snake[i - 1].X;
		snake[i].Y = snake[i - 1].Y;
	}
	snake[0].X = x;
	snake[0].Y = y;
	gotoxy(snake[0].X, snake[0].Y);
	printf("@");
}

void spreadfruit(block*snake, int snakelength, block* fruit)
{
	int isvalid;
	bool printed = false;
	(*fruit).X = rand() % COLS;
	(*fruit).Y = rand() % ROWS;
	for (isvalid = 0; isvalid < snakelength; isvalid++)
	{
		if (((*fruit).X != snake->X || (*fruit).Y != snake->Y) && (*fruit).X != 0 && (*fruit).Y != 0 && (*fruit).X < (COLS - 1) && (*fruit).Y < (ROWS - 1))
		{
			gotoxy((*fruit).X, (*fruit).Y);
			printf("$");
			printed = true;
			break;
		}
		else
		{
			spreadfruit(snake, snakelength, fruit);
		}
	}
	if (printed == false)
	{
		gotoxy(2, 2);
		printf("$");
	}
}

void endgame(bool status)
{
	gotoxy(0, 0);
	printf("\n\n\n\n");
	int i, j, choice;
	for (i = 0; i < 50; i++)
	{
		gotoxy(i, 0);
		printf("*");
		gotoxy(i, 13);
		printf("*");
	}
	for (j = 0; j < 14; j++)
	{
		gotoxy(0, j);
		printf("*");
		gotoxy(49, j);
		printf("*");
	}
	printf("\n\n");
	gotoxy(10, 7);
	if (status == true)
		printf("YOU WON THE GAME!!!!!");
	else
		printf("YOU LOST THE GAME....");
	gotoxy(0, 23);
}

void gameBoard()
{
	int i, j;
	for (i = 0; i < COLS; i++)
	{
		gotoxy(i, 0);
		printf("#");
		gotoxy(i, ROWS - 1);
		printf("#");
	}
	for (j = 0; j < ROWS; j++)
	{
		gotoxy(0, j);
		printf("#");
		gotoxy(COLS - 1, j);
		printf("#");
	}
}

block* reallocate(block* snake, int snakelength)
{
	int i;
	block* newsnake;
	newsnake = (block*)malloc(snakelength * sizeof(block));
	newsnake[snakelength - 1].X = snake[snakelength - 2].X;
	newsnake[snakelength - 1].Y = snake[snakelength - 2].Y;
	for (i = 0; i < snakelength - 1; i++)
	{
		newsnake[i].X = snake[i].X;
		newsnake[i].Y = snake[i].Y;
	}
	free(snake);
	return newsnake;
}

bool isquitting(bool PLAYING, int* choice)
{
	gotoxy(0, 0);
	switch (*choice)
	{
		case 1:
		{
			return rungame(&choice);
		}
		case 2:
		case 3:
		{
			gotoxy(0, 0);
			system("cls");
			printf("\n\nThis option is not yet avaliable, please choose a different one!\n\n");
			return true;
		}
		default:
		{
			gotoxy(0, 0);
			system("cls");
			printf("\n\nPlease choose a valid option!\n\n");
			return true;
		}
	}
}

bool rungame(int* choice)
{
	block* snake;
	block fruit = { 0, 0 };
	char c, t;
	int i;
	int numoffruits = 0;
	int x = 40, y = 12;
	int snakelength = 10;
	gotoxy(0, 0);
	system("cls");
	gameBoard();
	snake = (block*)malloc(snakelength * sizeof(block));
	checkAlloc(snake);
	gotoxy(x, y);
	updateSnake(snake, snakelength, x, y);
	c = getKey();
	t = c;
	while (c != ESC)
	{
		Sleep(100);
		if (_kbhit())
			t = getKey();
		if (t == RIGHT || t == LEFT || t == UP || t == DOWN || t == ESC)
		{
			c = t;
		}
		switch (c)
		{
		case RIGHT:
			x++;
			break;
		case DOWN:
			y++;
			break;
		case LEFT:
			x--;
			break;
		case UP:
			y--;
			break;
		}
		printsnake(snake, snakelength, x, y);
		if (numoffruits == 0)
		{
			spreadfruit(snake, snakelength, &fruit);
			numoffruits = 1;
		}
		for (i = 1; i < snakelength; i++)
		{
			if (((snake[0].X == snake[i].X) && (snake[0].Y == snake[i].Y)) || snake[0].X == 0 || snake[0].Y == 0 || snake[0].X == COLS - 1 || snake[0].Y == ROWS - 1)
			{
				system("cls");
				endgame(false);
				free(snake);
				return true;
			}
		}
		if (snake->X == fruit.X && snake->Y == fruit.Y)
		{
			snakelength++;
			if (snakelength == MAXSNAKESIZE)
			{
				system("cls");
				endgame(true);
				free(snake);
				return true;
			}
			else
			{
				snake = (block*)reallocate(snake, snakelength * sizeof(block));
				checkAlloc(snake);
				spreadfruit(snake, snakelength, &fruit);
			}
		}
		gotoxy(26, 81);
	}
	free(snake);
	return false;
}
