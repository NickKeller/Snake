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
	int iteration = 0;
	int time = 5;
	int ateFood = 0;
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
	DEBUG_PRINT("Drew the food\n");
				
	//main game loop
	while(1){
		
		DEBUG_PRINTF("Snake head row = %d\nSnake head col = %d\nIteration = %d\n",
					 snake->head->row, snake->head->col, iteration);
		
		//check for arrow keys
		if(KEY_DOWN_NOW(BUTTON_UP) && direction != DOWN){
			DEBUG_PRINT("Direction is now up\n");
			direction = UP;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT) && direction != LEFT){
			DEBUG_PRINT("Direction is now right\n");
			direction = RIGHT;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT) && direction != RIGHT){
			DEBUG_PRINT("Direction is now left\n");
			direction = LEFT;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN) && direction != UP){
			DEBUG_PRINT("Direction is now down\n");
			direction = DOWN;
		}
		
		//check for collision detection
		//check for hit the food
		if(snake->head->row == snake->food->row && snake->head->col == snake->food->col){
			ateFood = 1;
		}
		//hit top of screen?
		if(snake->head->row < 0){
			DEBUG_PRINTF("Snake hit top of screen. Row is %d\n", snake->head->row);
			result = 0;
			break;
		}
		//hit bottom of screen?
		if(snake->head->row > (159 - snake->head->height + 1)){
			DEBUG_PRINTF("Snake hit bottom of screen. Row is %d\n", snake->head->row);
			result = 0;
			break;
		}
		//hit left side of screen?
		if(snake->head->col < 0){
			DEBUG_PRINTF("Snake hit left of screen. Col is %d\n", snake->head->col);
			result = 0;
			break;
		}
		//hit right side of screen?
		if(snake->head->col > (239 - snake->head->width + 1)){
			DEBUG_PRINTF("Snake hit right of screen. Col is %d\n", snake->head->col);
			result = 0;
			break;
		}
		
		//did the snake hit itself?
		if(hitSelf(snake)){
			DEBUG_PRINT("Snake hit itself. Exiting\n");
			result = 0;
			break;
		}
		
		//save off the head's old position
		int oldRow = snake->head->row;
		int oldCol = snake->head->col;
		if(iteration > time){
			//update position of head, depending on direction
			if(direction == UP){
				snake->head->row -= snake->head->height;
			}
			if(direction == DOWN){
				snake->head->row += snake->head->height;
			}
			if(direction == LEFT){
				snake->head->col -= snake->head->width;
			}
			if(direction == RIGHT){
				snake->head->col += snake->head->width;
			}
		}
		
		//save off the tail's position
		int oldRowTail = snake->tail->row;
		int oldColTail = snake->tail->col;
		//update the rest of the snake every x iterations
		if(iteration > time){
			updateSnakePositions(snake, oldRow, oldCol);
		}	
		
		//wait for VBlank to draw
		waitForVblank();
		if(iteration > time){
			drawSnake(snake, ateFood, oldRowTail, oldColTail);
			iteration = 0;
			ateFood = 0;
		}	
		iteration++;
	}
	
	
	return result;
}



























