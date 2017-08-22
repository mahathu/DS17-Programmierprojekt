#include <stdio.h>

int main(int argc, char const *argv[])
{
	int startNode, targetNode, nodeCount, checkpointCount;
    long maxDistance;
    scanf("%d %d %ld", &startNode, &targetNode, &maxDistance);
    printf("Startnode: %d Targetnode: %d maxDistance: %ld\n", startNode, targetNode, maxDistance);
	return 0;
}	