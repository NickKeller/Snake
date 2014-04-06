
#include "list.h"
#include "mylib.h"
#include <string.h>
#include <debugging.h>

/*Sets pixel(r,c) to the given color*/
void setPixel(int r, int c, u16 color){
	*(videoBuffer + OFFSET(r,c,240)) = color;
}

/*Draws a filled rectangle of the given color with the 
  given width at (r,c)
*/
void drawRect(int r, int c, int width, int height, u16 color){
	int w;
	int h;
	//draw the rectangle
	for(h = 0; h < height; h++){
		for(w = 0; w < width; w++){
			setPixel(h + r, w + c, color);
		}
	}
}

/*Draws an outline of a rectangle of the given color
  with a given width and height at (r,c)
*/
void drawHollowRect(int r, int c, int width, int height, u16 color){
	int w;
	int h;
	//draw the rectangle
	for(h = 0; h < height; h++){
		for(w = 0; w < width; w++){
			//set the pixel only if the current pixel is on the outer edges
			//i.e. on the first or last row, or the first or last column
			if((h == 0 || h == (height - 1)) || (w == 0 || w == (width - 1))){
				setPixel(h + r, w + c, color);
			}
		}
	}
}

void drawImage3(int r, int c, int width, int height, int image){
	int h;
	for(h = 0; h < height; h++){
		//memmove(videoBuffer + OFFSET(r + h, c, 240), image, width * sizeof(u16));
		int color[] = {image};
		DMA[3].src = color;
		DMA[3].dst = videoBuffer + OFFSET(r + h, c, 240);
		DMA[3].cnt = (width) | DMA_SOURCE_FIXED | DMA_ON;
	}
	
	/*DMA[3].src = image;
	DMA[3].dst = videoBuffer + OFFSET(r,c,240);
	DMA[3].cnt = ((width * height) / 4) | DMA_ON;*/
}

void delay(int n){
	int i;
	volatile int x = 0;
	for(i = 0; i < n*10000; i++){x++;}
}

void waitForVblank(){
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


void clearScreen(){
	int clear[] = {BLACK};
	DMA[3].src = clear;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (240 * 160) | DMA_SOURCE_FIXED | DMA_ON;
}



