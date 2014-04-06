/*********************************
Name: Nick Keller
**********************************/
#ifndef MYLIB_H
#define MYLIB_H
typedef unsigned short u16;
//set the start of the video memory
#define BG2_ENABLE (1<<10)
#define MODE3 3
#define COLOR(r,g,b) ((r) | (g)<<5 | (b)<<10)
#define RGB(r,g,b) COLOR(r,g,b)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define BLUE COLOR(0,0,31)
#define GREEN COLOR(0,31,0)
#define BLACK COLOR(0,0,0)
#define OFFSET(r,c,rowlen) (((r) * (rowlen)) + (c))
#define REG_DISPCTL *((unsigned short *)(0x4000000))
#define SCANLINECOUNTER *((volatile unsigned short *)0x4000006)
#define SCREEN_WIDTH 239
#define SCREEN_HEIGHT 159
//Buttons
#define BUTTON_A (1<<0)
#define BUTTON_B (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START (1<<3)
#define BUTTON_RIGHT (1<<4)
#define BUTTON_LEFT (1<<5)
#define BUTTON_UP (1<<6)
#define BUTTON_DOWN (1<<7)
#define BUTTON_R (1<<8)
#define BUTTON_L (1<<9)
/*
Button bit listing
A-0
B-1
SELECT-2
START-3
RIGHT-4
LEFT-5
UP-6
DOWN-7
R-8
L-9
*/
#define BUTTONS *(volatile unsigned int *)0x4000130
#define KEY_DOWN_NOW(key) (~(BUTTONS) & (key))

//Snake Directions
#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

/* DMA */

typedef unsigned int u32;
typedef unsigned char u8;

typedef struct 
{
	const volatile void *src;
	const volatile void *dst;
	volatile 		 u32 cnt;
} DMAREC;

#define DMA ((volatile DMAREC *)0x040000B0)

#define REG_DMA0SAD         *(u32*)0x40000B0  // source address
#define REG_DMA0DAD         *(u32*)0x40000B4  // destination address
#define REG_DMA0CNT         *(u32*)0x40000B8  // control register

/* DMA channel 1 register definitions */
#define REG_DMA1SAD         *(u32*)0x40000BC  // source address
#define REG_DMA1DAD         *(u32*)0x40000C0  // destination address
#define REG_DMA1CNT         *(u32*)0x40000C4  // control register

/* DMA channel 2 register definitions */
#define REG_DMA2SAD         *(u32*)0x40000C8  // source address
#define REG_DMA2DAD         *(u32*)0x40000CC  // destination address
#define REG_DMA2CNT         *(u32*)0x40000D0  // control register

/* DMA channel 3 register definitions */
#define REG_DMA3SAD         *(u32*)0x40000D4  // source address
#define REG_DMA3DAD         *(u32*)0x40000D8  // destination address
#define REG_DMA3CNT         *(u32*)0x40000DC  // control register

/* Defines */
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define START_ON_FIFO_EMPTY 0x30000000

extern u16 *videoBuffer;

void setPixel(int,int,u16);
void drawRect(int,int,int,int,u16);
void drawHollowRect(int,int,int,int,u16);
void drawImage3(int,int,int,int,int);
void delay(int);
void waitForVblank(void);
int playGame(void);
void clearScreen(void);



#endif
