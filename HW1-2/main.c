#include <stdio.h>
#include <stdlib.h>

struct snode{
	int vertex;
	int color;
	int distance;
	struct snode *left;
	struct snode *right;
};

typedef struct snode node;

typedef enum {
	FALSE,	
	TURE
}flag_type; 

typedef enum {
	White, 
	Gray, 
	Black
}color_type; 

static node *first = NULL;
static node *tail = NULL;

int isQueueEmpty(void);
void insertNode(int,int);
int fatchNode(void);
int isVertexWhite(int);
void printQueue(void);

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int value,d;
	//node Node_x;
	
	while(1){
		printf("Enter a Node(-1 ends)==> ");
		scanf("%d", &value);
		if(value == -1) break;
		else {			
			if(isVertexWhite(value)){
				printf("Enter Node's distance==> ");
				scanf("%d", &d);
				insertNode(value,d);
			} 
			else printf("V%d has existed.\n", value);
		}		
	}
	printQueue();
	system("pause");
	
	d = fatchNode();
	printf("d=%d\n",d); 	
	printQueue();
	d = fatchNode();
	printf("d=%d\n",d); 	
	printQueue();
	
	system("pause");
	return 0;
}

/*Check the queue is empty or not*/
int isQueueEmpty(void){
	if(tail == NULL && first == NULL) return TURE;
	else return FALSE;
}
/*Put the new node at the back of queue*/
int isVertexWhite(int Vx){
	node *current = tail;
	
	while(current != NULL){
		if(current->vertex == Vx){	//if Vx has existed
			if(current->color == White) return TURE;
			else return FALSE;
		}
		else current = current->left;	//Find left node
	}
	return TURE;	//Vx doesnt's existed
}
void insertNode(int vertex, int distance){
	node *newNode;
	
	newNode = (node *)malloc(sizeof(node));	//set new memory space
	/*set the configration of newNode*/
	newNode->left = tail;
	newNode->vertex = vertex;
	newNode->right = NULL;
	newNode->distance = distance;
	newNode->color = Gray;
	
	if(newNode->left == NULL){ //for the first vexter
		first = newNode;
		tail = newNode;
		return;
	} 
	
	tail->right = newNode;
	tail = newNode;
}
/*Take the first node out of queue*/
int fatchNode(void){
	node *next = first->right;
	int d = first->distance;

	/*set "next" to be the first node*/
	if(next == NULL){
		free(first);	//free memory space
		first = next;
		tail = next;
	}
	else{
		next->left = first->left;
		printf("check\n");
		free(first);	//free memory space
		first = next;
	}		
	
	return d;
}
/*Display the whole queue on screen*/
void printQueue(void){
	node *current = first;
	
	if(isQueueEmpty()) {
		printf("Queue is Empty.\n");
		exit(1);
	}
	else{
		printf("Queue:");
		while(current != NULL){
			printf("[v%d](%d) ", current->vertex, current->distance);
			current = current->right;
		}
		printf("\n");
	}
}
