#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "User32.lib")

#define ROWS 20
#define COLS 40

void pause (void){
	fflush(stdin);
	getchar();
}

void initMatrix (int Matrix[ROWS][COLS]) {
	int i, j;

	for (i = 0; i < ROWS; i++){
		for (j = 0; j < COLS; j++){
			
			if(i == 0 || i == ROWS -1 || j == 0 || j == COLS -1){
				Matrix[i][j] = 5;

			} else {
				Matrix[i][j] = 0; // espacios vacios
			}
		}
	}
}

void printMatrix(int Matrix[ROWS][COLS]){
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++) 
		{
			if (Matrix[i][j] == 5){
				_textcolor(3);
				printf("#");
				_textcolor(7);
			}else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void initSnake(int Matrix[ROWS][COLS], int *snakeX, int *snakeY, int *direction){
	
	*snakeX = ROWS/2;
	*snakeY = COLS/2;

	Matrix[*snakeX][*snakeY] = 1;

}

void SnakeMovement(int Matrix[ROWS][COLS], int snakeX, int snakeY){
	if (snakeX >= 0 && snakeX < ROWS && snakeY >= 0 && snakeY < COLS) { //no hay colisiones con los bordes
		if (Matrix[snakeX][snakeY] == 0 || Matrix[snakeX][snakeY] == 1)
		{
			locate(snakeX, snakeY); // mira la posicion de la serpiente
			_textcolor(2);
			printf("*"); // actualiza la posicion de la serpiente
			_textcolor(7);
			Matrix[snakeX][snakeY] = 1;
		}
	}
}

void SnakeDirection(int *snakeX, int *snakeY, int *direction) {
	
	int prevDirection = *direction;

	fflush(stdin);
	if (_kbhit()!= 0) {
		int key = _getch();
	    switch (key) {
	        case 72: 
				if (prevDirection != 3) {
					*direction = 1; //arriba
				}
				break;
	            
			case 77:
				if (prevDirection != 4) {
					*direction = 2; //derecha
				}
				break;
	            
			case 80:
				if (prevDirection != 1) {
					*direction = 3; //abajo
				}
				break;
	            
			case 75:
				if (prevDirection != 2) {
					*direction = 4; //izquierda
				}
				break;

			default:
				break;
            }
        }

	if(*direction == 1){
		(*snakeX)--;
	}else if(*direction == 2){
		(*snakeY)++;
	}else if(*direction == 3){
		(*snakeX)++;
    }else if(*direction == 4){
		(*snakeY)--;
	}
}



void SnakeCollisions (int Matrix[ROWS][COLS], int snakeX, int snakeY, int *gameOver, int *score) {
	// Comprobar colisiones con los bordes
  		if (Matrix[snakeX][snakeY] == 5 || Matrix[snakeX][snakeY] == 3 || Matrix[snakeX][snakeY] == 1){      
			*gameOver = 1;
	
		} else if (Matrix[snakeX][snakeY] == 2) {
			*score = *score + 100;
			// cambiar el @ por * cuando la serpiente se coma el objeto
			Matrix[snakeX][snakeY] = 1;
			locate(snakeX, snakeY);
			_textcolor(2);
			printf("*");
			_textcolor(7);
	
		} else {
			SnakeMovement(Matrix, snakeX, snakeY);
		}
}

void SpawnObject(int Matrix[ROWS][COLS]) {
    int row, col;
    
	// rand() % (ROWS - 2) + 2 <- hecho de esta manera para excluir los bordes en la generacion de objetos

	// Genera '@' (puntaje)
    do {
        row = rand() % (ROWS - 2) + 2; 
        col = rand() % (COLS - 2) + 2;
    } while (Matrix[row][col] != 0);
    Matrix[row][col] = 2;

	// Imprimir '@'
    locate(row, col);
    _textcolor(1);            
    printf("@");
    _textcolor(7);

    // Genera 'X' (muerte)
    do {
        row = rand() % (ROWS - 2) + 2;
        col = rand() % (COLS - 2 + 2);
    } while (Matrix[row][col] != 0);
    Matrix[row][col] = 3;

	// Imprimir 'X'
    locate(row, col);
    _textcolor(4);            
    printf("X");
    _textcolor(7);
	
	
}
