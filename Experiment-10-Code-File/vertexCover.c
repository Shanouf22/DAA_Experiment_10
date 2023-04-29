//header files
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//graph handling
int** graphData; 
int* visited;
int* degree;
int numOfNodes;
int edgeCount=0;

//queue handling
int* nodesQueue;
int front=-1, rear=-1;
int soln[50];//to store the nodes which are to be included in the solution
int solnCount=0;

void enqueue(int elem){
    rear++;
    nodesQueue[rear]=elem;
}

int dequeue(){
	front++;
	return nodesQueue[front];
}

//function to find node with max degree
int getNodeWithMaxDeg(){
    int tempMax=0;
    for(int i=1; i<numOfNodes; i++){
        if(degree[i]>degree[tempMax])
            tempMax=i;
    }
    return tempMax;
}

//function to get approx answer of vertex cover problem
void approxVertexCover(){
    int currNode;
    while(edgeCount!=0){
        currNode=getNodeWithMaxDeg();
        printf("Current node added to the solution- %d\n",currNode);
        soln[solnCount++]=currNode;
        edgeCount-=2*degree[currNode];
        degree[currNode]=0;
        printf("Edges covered- {");
        for(int i=0; i<numOfNodes; i++){
            if(graphData[currNode][i]==1){
                degree[i]-=1;
                graphData[currNode][i]=0;
                graphData[i][currNode]=0;
                if(i>currNode)
                    printf("(%d,%d)",currNode,i);
                else
                    printf("(%d,%d)",i,currNode);
            }
        }
        printf("}\nEdges remaining- {");
        for(int i=0; i<numOfNodes; i++){
            for(int j=i+1; j<numOfNodes; j++){
                if(graphData[i][j]==1)
                    printf("(%d,%d)",i,j);
            }
        }
        printf("}\n\n");
    }
}

//main function
void main(){
	int node, degCount;
	
	printf("\nEnter the number of nodes in the graph -----> ");
	scanf("%d",&numOfNodes);
	
	graphData=(int**)malloc(numOfNodes*sizeof(int*));
	visited=(int*)malloc(numOfNodes*sizeof(int));
	degree=(int*)malloc(numOfNodes*sizeof(int));
	nodesQueue=(int*)malloc(numOfNodes*sizeof(int));
	
	for(int i=0; i<numOfNodes; i++){
		visited[i]=0;
		graphData[i]=(int*)malloc(numOfNodes*sizeof(int));
		for(int j=0; j<numOfNodes; j++){
			graphData[i][j]=0;
		}
	}
	
	printf("Nodes 0 to %d were initialized...\n",numOfNodes-1);
	
	printf("Enter the information regarding graph connectivity-\n\n");
	for(int i=0; i<numOfNodes; i++){
        degCount=0;
		printf("Enter the nodes connected to %d(-1 to terminate)- ",i);
		while(true){
			scanf("%d",&node);
			if(node==-1){
				break;
			}
            degCount++;
			graphData[i][node]=1;
		}
        edgeCount+=degCount;
        degree[i]=degCount;
	}

	//solving the vertex cover problem to get approx solution
    printf("\nFollowing data was obtained while solving the vertex cover problem-\n\n");
    approxVertexCover();
    printf("Hence, to cover all edges of the graph, following nodes should be explored- {");
    for(int i=0; i<solnCount-1; i++)
        printf("%d, ",soln[i]);
    printf("%d}",soln[solnCount-1]);
    printf("\n\n");

    free(visited);
    free(nodesQueue);
    free(degree);
    for(int i=0; i<numOfNodes; i++){
        free(graphData[i]);
    }
    free(graphData);
	
}