#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vertex *vertex_ptr;
typedef struct Vertex
{
    int val;
    int distance;
    vertex_ptr next;
} vertex_node;

typedef struct Graph {
    int vertices;
    vertex_ptr* adjcList;
}graph;

typedef struct qNode* q_ptr;
typedef struct qNode{
    int val;
    q_ptr next;
}q_node;

void insertEdge(graph, int, int);
void displayGraph(graph);
void insertToList(vertex_ptr* , int);
void BFS(graph, int);

void DFS_Visit(graph, int);
void DFS(graph,int);

void insertQ(q_ptr*, int);
int deleteQ(q_ptr*);
void displayQ(q_ptr*);

void push(int);
int pop();
void topologicalSort();

int t; // time
int *p, *s, *f;
char *c;

q_ptr stack = NULL;



int main()
{
    graph g;

    printf("\nEnter total number of vertices : ");
    scanf("%d", &g.vertices);
    
    g.adjcList = (vertex_ptr *)malloc(sizeof(vertex_node) * g.vertices);

    for(int i=0; i<g.vertices; i++){
        g.adjcList[i] = NULL;
    }
    // insertEdge(g,0, 1);
    // insertEdge(g,0, 5);
    // insertEdge(g,1, 2);
    // insertEdge(g,1, 5);
    // insertEdge(g,2, 3);
    // insertEdge(g,2, 4);
    // insertEdge(g,2, 5);
    // insertEdge(g,3, 4);
    // insertEdge(g,4, 5);   

    insertEdge(g,0, 1);
    insertEdge(g,0, 2);
    insertEdge(g,1, 3);
    insertEdge(g,2, 3);
    insertEdge(g,3, 4);
    insertEdge(g,3, 5);
    insertEdge(g,4, 5);
    displayGraph(g);

    printf("\n");
    BFS(g,0);
    printf("\nDFS : ");

    DFS(g,0);
    topologicalSort();

    // q_ptr q = NULL;
    
    //pointer is passed by value in c
    // insertQ(&q,1);
    // insertQ(&q,2);
    // insertQ(&q,3);
    // displayQ(&q);
}

void insertEdge(graph g, int a, int b)
{
    insertToList(&g.adjcList[a], b);

    // if graph is not directed then use this line also
    // insertToList(&g.adjcList[b], a);

    //other method without using above functions
    // vertex_ptr tmp = (vertex_ptr)malloc(sizeof(vertex_node));
    // tmp->val = b;
    // tmp->next = g.adjcList[a];
    // g.adjcList[a] = tmp;

    // vertex_ptr tmp2 = (vertex_ptr)malloc(sizeof(vertex_node));
    // tmp2->val = a;
    // tmp2->next = g.adjcList[b];
    // g.adjcList[b] = tmp2;
}

void insertToList(vertex_ptr* root, int x)
{
    // printf("%p",&root);
    vertex_ptr tmp = (vertex_ptr)malloc(sizeof(vertex_node));
    tmp->val = x;
    tmp->next = NULL;
    // tmp->val = x;
    // tmp->next = *root;
    // *root = tmp;

    if(*root == NULL){
        *root = tmp;
        (*root)->next = *root;
    }
    else{
        tmp->next = (*root)->next;
        (*root)->next = tmp;
        *root = tmp;
    }
}

void displayGraph(graph g)
{
    for (int i = 0; i < g.vertices; i++)
    {
        printf("\n\nAdjacent vertices of %d : ", i);
        if(g.adjcList[i] != NULL){
            vertex_ptr tmp = g.adjcList[i]->next;
            do
            {
                printf("%d ", tmp->val);
                tmp = tmp->next;
            }
            while (tmp != g.adjcList[i]->next);
            printf("\n");
        }
    }
}

void insertQ(q_ptr* q, int x){
    q_ptr tmp = (q_ptr) malloc (sizeof(q_node));
    tmp->val = x;
    tmp->next = NULL;
    if (tmp != NULL){
        if(*q != NULL){
            tmp->next = (*q)->next;
            (*q)->next = tmp;
            *q = tmp;
        }
        else{
            *q = tmp;
            (*q)->next = *q;
        }
    }
    else{
        printf("Memory is full");
    }
}

int deleteQ(q_ptr* q){
    if(q == NULL){
        return -1;
    }
    q_ptr tmp = (*q)->next;
    if ((*q)->next == *q){ // only one element is left in queue
        *q = NULL;
    }
    else{
        (*q)->next = tmp->next;
    }
    int x = tmp->val;
    free(tmp);
    return x;
}

bool isQEmpty(q_ptr q){
    return q == NULL;
}

void displayQ(q_ptr* q){
    //*q will store the item which is last inserted
    //*q->next will store the item which was inserted first

    if (*q != NULL){
        q_ptr tmp = (q_ptr) malloc(sizeof(q_node));
        tmp = (*q)->next; 
        do{
            printf("%d ",tmp->val);
            tmp = tmp->next;
        }
        while(tmp != (*q)->next);
        printf("\n");
    }
    else {
        printf("Queue is empty !!");
    }
}

void BFS(graph g, int startVertex){
    //p - parent, d - distance, c - color
    // q_ptr q = (q_ptr) malloc(sizeof(q_node));

    q_ptr q = NULL;
    int p[g.vertices],d[g.vertices];
    char c[g.vertices];
    for(int i=0; i<g.vertices; i++){
        // p[i] = NULL;
        p[i] = g.vertices;
        c[i] = 'w';
        d[i] = g.vertices;
    }
    d[startVertex] = 0;
    c[startVertex] = 'g';

    insertQ(&q,startVertex);
    printf("%d ",startVertex);
    while(!isQEmpty(q)){
        int u = deleteQ(&q);
        if (g.adjcList[u] != NULL){ // can be null in case of disconnected graph
            vertex_ptr tmp = g.adjcList[u]->next;
            do{
                int v = tmp->val;
                if(c[v] == 'w'){
                    printf("%d ",v);
                    p[v] = u;
                    d[v] = d[u] + 1;
                    c[v] = 'g';
                    insertQ(&q,v);
                }
                tmp = tmp->next;
            }
            while(tmp != g.adjcList[u]->next);
        }
    }
    printf("\n");
}


void DFS(graph g, int startVertex){
    t = 0;
    // int p[g.vertices];
    // char c[g.vertices];
    // int s[g.vertices];
    // int f[g.vertices]; //finish time

    p = (int*) malloc(sizeof(int) * g.vertices);
    s = (int*) malloc(sizeof(int) * g.vertices);
    f = (int*) malloc(sizeof(int) * g.vertices);
    c = (char*) malloc(sizeof(char) * g.vertices);

    for(int i=0; i<g.vertices; i++){
        p[i] = g.vertices;
        c[i] = 'w';
    }

    
    // for(int v=0; v<g.vertices; v++)
    //     if(c[v] == 'w')
    //         DFS_Visit(g,v);  
    c[startVertex] = 'g';
    t++;
    printf("%d ",startVertex);
    if (g.adjcList[startVertex] != NULL){
        vertex_ptr tmp = g.adjcList[startVertex]->next;
        do{
            int v = tmp->val;
            if(c[v] == 'w')
                DFS_Visit(g,v);
            tmp = tmp->next;
        }
        while(tmp != g.adjcList[startVertex]->next);
    }
    
    push(startVertex);
    printf("\n");
}

void DFS_Visit(graph g, int v){
    t++;
    c[v] = 'g';
    printf("%d ",v);
    s[v] = t;
    if (g.adjcList[v] != NULL){
        vertex_ptr tmp = g.adjcList[v]->next;
        do{
            int u = tmp->val;
            if(c[u] == 'w'){
                p[u] = v;
                DFS_Visit(g,u);
            }
            tmp = tmp->next;
        }
        while(tmp != g.adjcList[v]->next);
    }
    t++;
    c[v] = 'b';
    f[v] = t;
    push(v);
}

void push(int v){
    q_ptr tmp = (q_ptr) malloc(sizeof(q_node));
    tmp->val = v;
    tmp->next = stack;
    stack = tmp;
}

int pop(){
    if (stack != NULL){
        q_ptr tmp = stack;
        stack = stack->next;
        int v = tmp->val;
        free(tmp);
        return v;
    }
    return NULL;
}

void topologicalSort(){
    if(stack != NULL){
        q_ptr tmp = stack;
        while(tmp){
            printf("%d ",tmp->val);
            tmp = tmp->next;
        }
        printf("\n");
    }
    else 
        printf("\nGraph is empty");
}