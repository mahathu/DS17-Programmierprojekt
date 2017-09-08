#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXLINE 100
#define TRUE 1
#define FALSE 0

typedef struct edge{
	int from;
	int to;
	long weight;
	struct edge *next;
} edge;

typedef struct checkpoint{
	int id;
	struct checkpoint *next;
} checkpoint;

typedef struct nodeEdge{
	int to;
	long weight;
	struct nodeEdge *next;
} nodeEdge;

typedef struct{
	nodeEdge *head;
	nodeEdge *tail;
	short isSafehouse;
	short isPossibleSafehouse;
} node;

edge *pushEdgeAfter(edge *before, int from, int to, long weight){
	edge *newEdge = malloc(sizeof(edge));
	newEdge->from = from;
	newEdge->to = to;
	newEdge->weight = weight;
	newEdge->next = NULL;

	before->next = newEdge;

	return newEdge;
}

void pushCheckpoint(checkpoint *head, int id){
	checkpoint *current = head;
	while(current->next != NULL)
		current = current->next;
	checkpoint *new = malloc(sizeof(checkpoint));
	new->id = id;
	new->next = NULL;

	current->next = new;
}

void addEdgeToNode(node *nodePointer, int to, long weight){
	nodeEdge *current = nodePointer->head;
	while(current->next != NULL){
		current = current->next;
	}

	nodeEdge *new = malloc(sizeof(nodeEdge));
	new->to = to;
	new->weight = weight;
	new->next = NULL;
	
	current->next = new;
}

void printEdge(edge *e){
	printf("%d -> %d (%ld)\n", e->from, e->to, e->weight);
}

void printList(edge *start){
	edge *current = start;
	while(current != NULL){
		printEdge(current);
		current = current->next;
	}
}

void printEdges(int nodeID, node *nodePointer){
	nodeEdge *current = nodePointer->head->next;
	while(current != NULL){
		printf("%d ", current->to);
		current = current->next;
	}
}

/* fills distances array with shortest distance from start node */
void dijkstra(int startNode, int nodeCount, node *nodes[], long distances[]){
	for (int i = 0; i < nodeCount; ++i)
	{
		distances[i] = LONG_MAX;
	}
	distances[startNode] = 0;
}

int main(int argc, char const *argv[])
{
	int startID, targetID, maxNode = 0;
	long maxWeight;
	edge *head = malloc(sizeof(edge));
	checkpoint *checkpointHead = malloc(sizeof(checkpoint));
	
	scanf("%d %d %ld", &startID, &targetID, &maxWeight);
	getchar();

	int to,from;
	long weight;
	char puffer[MAXLINE];
	fgets(puffer, MAXLINE, stdin);
	edge *newEdge = head;

	while(sscanf(puffer, "%d %d %ld", &from, &to, &weight) == 3){
		newEdge = pushEdgeAfter(newEdge, from, to, weight);
		if(from > maxNode)
			maxNode = from;
		if(to > maxNode)
			maxNode = to;

		if(fgets(puffer, MAXLINE, stdin) == NULL){
			printf("%s\n", "ERROR: no checkpoints given");
			return 1;
		}
	}

	int newCheckpointID;
	while(1){
		sscanf(puffer, "%d", &newCheckpointID);
		pushCheckpoint(checkpointHead, newCheckpointID);
		if(fgets(puffer, MAXLINE, stdin) == NULL)
			break;
	}

	//printList(head);
	//printf("maxNode: %d\n", maxNode);

	node *nodes[maxNode+1];
	for(int i=0; i<maxNode+1; i++){
		nodes[i] = malloc(sizeof(node));
		nodes[i]->head = malloc(sizeof(nodeEdge));
		nodes[i]->isPossibleSafehouse = FALSE;
	}
	checkpoint *currentCheckpoint = checkpointHead;
	edge *currentEdge = head;
	while(currentEdge->next != NULL){
		currentEdge = currentEdge->next;
		printf("Adding edge: from %d to %d\n", currentEdge->from, currentEdge->to);
		addEdgeToNode(nodes[currentEdge->from], currentEdge->to, currentEdge->weight);
	}
	while(currentCheckpoint->next != NULL){
		currentCheckpoint = currentCheckpoint->next;
		nodes[currentCheckpoint->id]->isSafehouse = TRUE;
	}


	for(int i=0; i<maxNode+1; i++){
		printf("Node #%d\n", i);
		printf(" is safehouse: %d\n", nodes[i]->isSafehouse);
		printf("Points towards: ");

		printEdges(i, nodes[i]);
		printf("\n\n");
	}

	long distances[maxNode+1];
	dijkstra(3, maxNode + 1, nodes, distances);
	for(int i=0; i<maxNode+1; i++){
		printf("%ld\n", distances[i]);
	}

	return 0;
}