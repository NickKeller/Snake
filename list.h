#ifndef LIST_H
#define LIST_H

typedef struct lnode {
	struct lnode* next;
	struct lnode* prev;
	int row;
	int col;
	int width;
	int height;
} NODE;

typedef struct llist {
	NODE* head;
	NODE* tail;
	NODE* food;
	int size;
} LIST;

LIST *initializeSnake(void);
LIST* create_list();
void list_add(LIST* llist, int row, int col, int width, int height);
void list_del(LIST* llist, int index);
NODE* create_node(int row, int col, int width, int height);
void print_node(NODE* node);
void updateSnakePositions(LIST* snake, int oldRow, int oldCol);
void drawSnake(LIST* snake, int ateFood, int oldRow, int oldCol);
int hitSelf(LIST* snake);

#endif
