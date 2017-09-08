#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
/*listNode *newNode = malloc(sizeof(listNode));
	listNode *newNode2 = malloc(sizeof(listNode));
	listNode *newNode3 = malloc(sizeof(listNode));
	edge newEdge,newEdge2,newEdge3;
	newEdge.to = 10;
	newEdge.from = 20;
	newEdge.weight = 1000;
	newNode->element = newEdge;

	newEdge2.to = 20;
	newEdge2.from = 40;
	newEdge2.weight = 2000;
	newNode2->element = newEdge2;

	newEdge3.to = 40;
	newEdge3.from = 80;
	newEdge3.weight = 4000;
	newNode3->element = newEdge3;

	addToList(head, newNode);
	addToList(head, newNode2);
	addToList(head, newNode3);
	printList(head);
	printf("\n");
	swap(newNode, newNode3);
	printList(head);
	printf("\n");
	swap(newNode2, newNode3);
	printList(head);*/
/* 
	linked list instead of array representing a heap representing a binary queue
	linked list 0th element is empty, root is first, left child second, right child third
	if a node is in array[k], then its left child is in array[k*2], and its right child is in array[k*2 + 1]
	If a node is in array[k], then its parent is in array[k/2]


	Heap/Priority queue enthält alle unbesuchten Knoten bei Durchlauf von Dijkstra
	
	gesamter Graph ist als linked list gespeichert
*/

typedef struct{
	int from;
	int to;
	long weight;
} edge;

typedef struct listNode{
	edge element;
	struct listNode *next;
} listNode;

/* helper function to print a list element in a human readable format */
void printListElement(listNode *node){
	edge element = node->element;
	printf("%d -> %d (%ld)\n", element.from, element.to, element.weight);
}

/* helper function to print the linked list, starting from the provided node */
void printList(listNode *start){
	listNode *current = start;

	int listPosition = 0;
	while(current != NULL){
		printf("#%.6d: ", listPosition++);
		printListElement(current);
		current = current->next;
	}
}

/* adds an element to the end of the list and returns a pointer to the new last element */
listNode *addToList(listNode *head, listNode *newNode){
	listNode *current = head;
	while(current->next != NULL)
		current = current->next;
	current->next = newNode;
}

/* swaps two elements in the list by swapping their elements*/
void swap(listNode *a, listNode *b){
	edge tmp = a->element;
	a->element = b->element;
	b->element = tmp;
}

/* adds a new element to the heap by adding it to the list and moving it to the correct spot */
int addToHeap(listNode *head, edge newElement){
	listNode *newNode = malloc(sizeof(listNode));
	if(!newNode) return 0; //return 0 if malloc failed
	newNode->element = newElement;
	addToList(head, newNode);
	return 1;
}

int main(int argc, char const *argv[])
{
	listNode *graphHead = malloc(sizeof(listNode)); /* first element of the linked list containing all nodes */
	if(graphHead == NULL){
		printf("Error!\n");
	} else printf("Success!\n");

	
	edge e;
	e.to = 10;
	e.from = 9;
	e.weight = 1000000;
	listNode *prev = graphHead;
	for(int i=0; i<100; i++){
		prev->next = 
	}
	//printList(head);
	return 0;
}