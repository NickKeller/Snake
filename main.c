#include "list.h"
#include "mylib.h"
#include "WelcomeScreen.h"
#include "WinningScreen.h"
#include "LosingScreen.h"

#include <debugging.h>
#include <stdio.h>

u16 *videoBuffer = ((u16 *)(0x6000000));

int main(void){
	//set mode 3
	REG_DISPCTL = MODE3 | BG2_ENABLE;
		
	//display the welcome screen
	displayWelcomeScreen();
	while(1){
		clearScreen();
		int result = playGame();
		//kicked out, decide whether he won or not
		if(result == 0){
		//player lost
			displayLosingScreen();
		}
		
		else if (result == 1){
		//player won
			displayWinningScreen();
		}
		//wait for player to hit reset
		while(!KEY_DOWN_NOW(BUTTON_SELECT));
	}
}

int playGame(){
	volatile int direction = RIGHT;
	int result = 0;
	//initialize the snake
	LIST *snake = initializeSnake();
	//draw the initial snake
	NODE* toDraw = snake->head;
	while(toDraw != NULL){
		DEBUG_PRINT("Drawing a new portion of the snake\n");
		drawImage3(toDraw->row, toDraw->col, toDraw->width, toDraw->height, WHITE);
		toDraw = toDraw->next;
	}
	//draw the food
	drawImage3(snake->food->row, snake->food->col, snake->food->width,
				snake->food->height, WHITE);
				
	//main game loop
	while(1){
		//check for arrow keys
		if(KEY_DOWN_NOW(BUTTON_UP)){
			DEBUG_PRINT("Direction is now up\n");
			direction = UP;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT)){
			DEBUG_PRINT("Direction is now right\n");
			direction = RIGHT;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT)){
			DEBUG_PRINT("Direction is now left\n");
			direction = LEFT;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN)){
			DEBUG_PRINT("Direction is now down\n");
			direction = DOWN;
		}
		
		//check for collision detection
	}
	
	
	return result;
}



























