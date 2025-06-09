#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#pragma comment(lib, "User32.lib")

// DAVID RODRIGUEZ -- NIU: 1751508

#define ROWS 20
#define COLS 40

void initMatrix(int Matrix[ROWS][COLS]);
void printMatrix(int Matrix[ROWS][COLS]);
void initSnake(int Matrix[ROWS][COLS], int *snakeX, int *snakeY, int *direction);
void SnakeDirection(int *snakeX, int *snakeY, int *direction);
void SnakeCollisions(int Matrix[ROWS][COLS], int snakeX, int snakeY, int *gameOver, int *score);
void SpawnObject(int Matrix[ROWS][COLS]);
void enableAnsiSupport(void) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "No s'ha pogut obtenir el gestor de sortida\n");
		return;
		}
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) {
		fprintf(stderr, "No s'ha pogut obtenir el mode de la consola\n");
		return;
	}
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode)) {
		fprintf(stderr, "No s'ha pogut activar el suport per codis ANSI\n");
	}
}
void locate(int row, int col){
	printf("\033[%d;%dH", row, col); // Seq��ncia d'escapada ANSI.
}

int main(int argc, char *argv[]){
	enableAnsiSupport();
	srand(time(0));

	int Matrix[ROWS][COLS];
    int snakeX, snakeY;
	int gameOver = 0, score = 0;
	int direction = 2;

    initMatrix(Matrix);
	initSnake(Matrix, &snakeX, &snakeY, &direction);
	_clrscr();
	printMatrix(Matrix);

    do {
		locate(ROWS + 1, 0);
		printf("Score: %d\n", score);
		score ++;
		SnakeDirection(&snakeX, &snakeY, &direction);
		SnakeCollisions(Matrix, snakeX, snakeY, &gameOver, &score);
		
		if (rand() % 10 == 0){
			SpawnObject(Matrix);
		}

        Sleep(100);

    } while (gameOver != 1);

    locate(ROWS / 2, COLS / 2 -10);
    printf("GAME OVER!! your score: %d\n", score);
	
	locate(ROWS + 5, 0); // Justo debajo de la matriz
    printf("Press 'q' to quit\n");

    return 0;
}
