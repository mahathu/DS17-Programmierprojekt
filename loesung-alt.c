#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000
typedef struct edgeNode{
	int from;
	int to;
	long weight;
	struct edgeNode *next;
} edgeNode;

typedef struct checkpointNode{
	int nodeVal;
	struct checkpointNode *next;
} checkpointNode;

int main(int argc, char const *argv[])
{
	void pushCheckpointNode(checkpointNode *head, int nodeVal);
	void pushEdgeNode(edgeNode *head, long from, long to, long weight);
	void fillCheckpointArray(int checkpoints[], checkpointNode *head);
	int getMaxNode(edgeNode *head);
	int getNumberOfCheckpoints(checkpointNode *head);
	void destroyCheckpointList(checkpointNode *head);
	void destroyEdgeList(edgeNode *head);
	void fillAdjacencyMatrix(long **matrix, edgeNode *head, int nodeCount);
	void printMatrix(long **matrix, int nodeCount);

	edgeNode *edgeHead = malloc(sizeof(edgeNode));
	edgeHead->next = NULL;

	checkpointNode *checkpointHead = malloc(sizeof(checkpointNode));
	checkpointHead->next = NULL;

	int startedgeNode, targetedgeNode, nodeCount, checkpointCount;
    long maxDistance;

    scanf("%d %d %ld", &startedgeNode, &targetedgeNode, &maxDistance);
    //printf("StartedgeNode: %d TargetedgeNode: %d maxDistance: %ld\n", staredgeNode, targeedgeNode, maxDistance);
	

	getchar(); //remove linefeed that wasn't picked up from scanf call earlier

	int to,from;
	long weight;
	char puffer[MAXLINE];
	fgets(puffer, MAXLINE, stdin);
	while(sscanf(puffer, "%d %d %ld", &from, &to, &weight) == 3){
		pushEdgeNode(edgeHead, from, to, weight);

		//printf("%s",puffer);
		if(fgets(puffer, MAXLINE, stdin) == NULL){
			printf("%s\n", "ERROR: no checkpoints given");
			return 1;
		}
	}

	int newCheckpoint;
	while(1){
		sscanf(puffer, "%d", &newCheckpoint) == 1;
		pushCheckpointNode(checkpointHead, newCheckpoint);
		if(fgets(puffer, MAXLINE, stdin) == NULL)
			break;
	}

	nodeCount = getMaxNode(edgeHead);

	long **adjacencyMatrix = (long **)malloc(nodeCount * sizeof(long *));
    for(int i=0; i<nodeCount; i++)
		adjacencyMatrix[i] = (long *)malloc(nodeCount * sizeof(long));

    checkpointCount = getNumberOfCheckpoints(checkpointHead);

    int checkpoints[checkpointCount];
    fillCheckpointArray(checkpoints, checkpointHead);
    destroyCheckpointList(checkpointHead);

    fillAdjacencyMatrix(adjacencyMatrix, edgeHead, nodeCount);
    printMatrix(adjacencyMatrix,nodeCount);
    destroyEdgeList(edgeHead);
	return 0;
}

void pushEdgeNode(edgeNode *head, long from, long to, long weight){
	edgeNode *current = head;
	while(current->next != NULL)
		current = current->next;

	edgeNode *newNode = malloc(sizeof(edgeNode));

	newNode->from = from;
	newNode->to = to;
	newNode->weight = weight;
	newNode->next = NULL;

	current->next = newNode;
}

void pushCheckpointNode(checkpointNode *head, int nodeVal){
	checkpointNode *current = head;
	while(current->next != NULL)
		current = current->next;

	checkpointNode *newNode = malloc(sizeof(checkpointNode));
	newNode->nodeVal = nodeVal;
	newNode->next = NULL;

	current->next = newNode;
}

/*void printList(checkpointNode *head){
	checkpointNode *current = head->next;

	while(current != NULL) {
		printf("%d\n", current->nodeVal);
		current = current->next;
	}
}*/

int getMaxNode(edgeNode *head){
	int max = 0;
	edgeNode *current = head->next;

	while(current != NULL) {
		if(current->to > max)
			max = current->to;
		if(current->from > max)
			max = current->from;
		current = current->next;
	}
	//size of the adjacency matrix, 0 can be a node as well
	return max+1;
}

int getNumberOfCheckpoints(checkpointNode *head){
	checkpointNode *current = head;
	int n=0;
	while(current->next != NULL){
		current = current->next;
		n++;
	}
	return n;
}

//Arrays are call by reference so we can put this in a seperate function
void fillCheckpointArray(int checkpoints[], checkpointNode *head){
	checkpointNode *current = head;
	int i=0;
	while(current->next != NULL){
		current = current->next;
		checkpoints[i++] = current->nodeVal;
	}
}

void fillAdjacencyMatrix(long **matrix, edgeNode *head, int nodeCount){
	//iterate through the linked list of triples gathered before to fill the empty adjacency matrix.
	for(int i=0;i<nodeCount;i++){
		for(int j=0; j<nodeCount; j++){
			matrix[i][j] = (i==j) ? 0 : LONG_MAX;
		}
	}
		
	edgeNode *current = head;
	while(current->next != NULL){
		current = current->next;
		printf("%d %d %ld\n", current->from, current->to, current->weight);
		matrix[current->from][current->to] = current->weight;
	}
}

void printMatrix(long **matrix, int nodeCount){
	for(int i=0;i<nodeCount;i++){
		for(int j=0; j<nodeCount; j++){
			printf("%19ld ",matrix[i][j]);
		}
		printf("\n");
	}
}

void destroyCheckpointList(checkpointNode *head){
	checkpointNode *current = head;
	checkpointNode *next;
	while(current->next != NULL){
		next = current->next;
		free(current);
		current = next;
	}
}

void destroyEdgeList(edgeNode *head){
	edgeNode *current = head;
	edgeNode *next;
	while(current->next != NULL){
		next = current->next;
		free(current);
		current = next;
	}
}