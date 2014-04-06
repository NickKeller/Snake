#ifndef LIST_H
#define LIST_H

typedef struct lnode {
	struct lnode* next;
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

#endif
