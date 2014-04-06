#include "list.h"
#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * This function will create a new list and return a pointer to that list.
 */
LIST* create_list()
{
	LIST *l = malloc(sizeof(LIST));
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	l->food = NULL;
	return l;
}

/**
 * This function will add the given data to the linked list (llist)
 */
void list_add(LIST* llist, int row, int col, int width, int height)
{
	//printf("ADDING TO THE LIST\n");
	NODE *node = create_node(row, col, width, height);
	//first, check to see if the list is brand new
	if((llist->head == NULL) &&(llist->tail == NULL)){
		//new list, point the head and tail toward the newly created node
		llist->head = node;
		llist->tail = node;
		
	}
	//else, make the new node the tail
	else{
		//instantiate node as the new tail of the list
		llist->tail->next = node;
		node->prev = llist->tail;
		node->next = NULL;
		llist->tail = node;
	}
	llist->size++;
	return;
}

/**
 * This function will remove the data located at the given index in the list (llist)
 * just like the above function, but removes the node instead
 * remember to free the node and re-arrange your pointers as needed!
 */
void list_del(LIST* llist, int index)
{
	if((index > (llist->size - 1)) || (index < 0)){
		//printf("Error, index %d is out of bounds\n",index);
		return;
	}
	//check to see if the user wants to remove the head
	else if(index == 0){
		//wants to remove the head
		NODE *toDelete = llist->head;
		llist->head = toDelete->next;
		free(toDelete);
		llist->size--;
	}
	else{
		NODE *cur = llist->head;
		int i;
		for(i = 0; i < (index - 1); i++){
			cur = cur->next;
		}
		//have the node we want, time to remove it
		NODE *toDelete = cur->next;
		cur->next = toDelete->next;
		if(cur->next == NULL){
			llist->tail = cur;
		}
		free(toDelete);
		llist->size--;
	}
}

/**
 * This function will create a node from the given data and return a pointer to that node.
 */
NODE* create_node(int row, int col, int width, int height)
{
	NODE *node = malloc(sizeof(NODE));
	node->row = row;
	node->col = col;
	node->width = width;
	node->height = height;
	return node;
}

/** 
 * This function will print a node out in a nicely formatted way. Do whatever you want, just try to make it easy to read.
 * Note you will be using this to traverse over the list and print the nodes.
 */
void print_node(NODE* node)
{
	//printf("-------------------------------\n");
	//printf("Node value = %d\n",node->data);
	//print the next node's value only if node isn't the tail
	if(node->next != NULL){
		//printf("Next Node's value = %d\n",node->next->data);	
	}
	else{
	//	printf("This node is the tail\n");
	}
//	printf("-------------------------------\n");
//	printf("-------------------------------\n");
	return;
}
/*
	This function will initialize the snake, and the food that will cause the snake to grow 
*/
LIST* initializeSnake(){
	LIST * l = create_list();
	//establish 3 sections
	int col = 60;
	for(int i = 0; i < 5; i++){
		list_add(l,0,col,10,10);	
		col -= 10;
	}
	int foodRow = 100;
	int foodCol = 100;
	l->food = create_node(foodRow, foodCol, 10, 10);
	return l;
}
/*
	updates the positions of the snake
*/
void updateSnakePositions(LIST* snake, int oldRow, int oldCol){
	NODE* current = snake->tail;
	while(current->prev != snake->head){
		current->row = current->prev->row;
		current->col = current->prev->col;
		current = current->prev;
	}
	current->row = oldRow;
	current->col = oldCol;
}

void drawSnake(LIST* snake, int ateFood, int oldRow, int oldCol){
	//draw the new location of the head of the snake
	drawImage3(snake->head->row, snake->head->col, snake->head->width,
				 snake->head->height, WHITE);
	//only draw over the tail if it didn't eat food
	if(ateFood == 0){
		drawImage3(oldRow, oldCol, snake->tail->width, 
					snake->tail->height, BLACK);
	}
	
}





