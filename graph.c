#include <stdio.h>
#include <stdlib.h>

typedef struct vertex* vertex_ptr;
typedef struct vertex{
    int val;
    int distance;
    vertex_ptr next;
}vertex_node; 

typedef struct q_node* q_ptr;
typedef struct q_node{
    int val;
    q_ptr next;
}qNode;

q_ptr front=NULL,rear=NULL;

void insertQ(int);
int deleteQ();
void displayQ();


void insertEdge(int,int);
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
    insertEdge(2,3);
    insertEdge(2,4);
    insertEdge(2,5);
    insertEdge(3,4);
    insertEdge(4,5);
    displayGraph();
    BFS(0);
    
    printf("\n");
    return 0;
}

void insertEdge(int a, int b){
    vertex_ptr tmp = (vertex_ptr) malloc(sizeof(vertex_node));
    tmp->val = b;
    tmp->next = graph[a];
    graph[a] = tmp;
    
    vertex_ptr tmp2 = (vertex_ptr) malloc(sizeof(vertex_node));
    tmp2->val = a;
    tmp2->next = graph[b];
    graph[b] = tmp2;
    
}



void displayGraph(){
    for(int i = 0; i<size; i++){
        printf("\nAdjacent vertices of %d : ",i);
        vertex_ptr tmp = graph[i];
        while(tmp){
            printf("%d ",tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void insertQ(int x){
    q_ptr tmp = (q_ptr) malloc(sizeof(q_ptr));
    tmp->val = x;
    tmp->next = NULL;
    if(rear == NULL){
        front = rear = tmp;
    }
    else{
        rear->next = tmp;
        rear = tmp;
    }
}

int deleteQ(){
    if(front == NULL){
        return -1;
    }
    q_ptr tmp = front;
    front = front->next;
    if (front == NULL)
        rear = NULL;
    int x = tmp->val;
    free(tmp);
    return x;
}


void displayQ(){
    q_ptr tmp = front;
    while(tmp){
        printf("%d",tmp->val);
        tmp=tmp->next;
    }
}

void BFS(int s){
    printf("\n\nBFS(%d) :\n\n",s);
    int p[size],d[size];
    char c[size];
    
    for(int i=0; i<size; i++){
        p[i] = NULL;
        c[i] = 'w';
        d[i] = size;
    }
    d[s] = 0;
    c[s] = 'g';
    insertQ(s);
    displayQ();
    while(rear!=NULL){
        int u = deleteQ();
        vertex_ptr tmp = graph[u];
        while(tmp){
            int v = tmp->val;
            if(c[v] == 'w'){
                printf("%d ",v);
                p[v] = u;
                d[v] = d[u] + 1;
                c[v] = 'g';
                insertQ(v);
            }
            tmp = tmp->next;
        }
    }
}









