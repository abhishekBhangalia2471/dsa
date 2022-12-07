#include <stdio.h>
#include <stdlib.h>

typedef struct vertex* vertex_ptr;
typedef struct vertex{
    int val;
    int distance;
    vertex_ptr next;

}vertex_node; 


void insertEdge(int,int);
void insertQ(vertex_ptr root, int x);
// void insertGraph();
// void BFS();
void displayGraph();

vertex_ptr* graph;
int size;

int main(){
    
    printf("\nEnter size of graph : ");
    scanf("%d",&size);
    graph = (vertex_ptr*) malloc(sizeof(vertex_node) * size);

    insertEdge(0,1);
    insertEdge(0,5);
    insertEdge(1,2);
    insertEdge(1,5);
    insertEdge(1,0);
    insertEdge(2,1);
    insertEdge(2,3);
    insertEdge(2,4);
    insertEdge(2,5);
    insertEdge(3,2);
    insertEdge(3,4);
    insertEdge(4,2);
    insertEdge(4,3);
    insertEdge(4,5);
    insertEdge(5,0);
    insertEdge(5,1);
    insertEdge(5,2);
    insertEdge(5,4);
    displayGraph();
    printf("\n");
}

void insertEdge(int a, int b){
    insertQ(graph[a],b);
}

void insertQ(vertex_ptr root, int x){
    vertex_ptr tmp = (vertex_ptr) malloc(sizeof(vertex_node));
    tmp->val = x;
    tmp->next = root;
    root = tmp;
    printf("%d",root->val);
    if (root->next)
    printf("next : %d",root->next->val);
}

void displayGraph(){
    for(int i = 0; i<size; i++){
        printf("\n\nAdjacent vertices of %d : ",i);
        vertex_ptr tmp = graph[i];
        if(tmp)
            do{
                printf("%d ",tmp->val);
                tmp = tmp->next;
            }
            while (tmp->val != i);
    }
}