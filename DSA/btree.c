#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// order 5
// max keys = 4
// min keys = 2
// max children = 5
// min children = 3
// #define MAX 5 // max children
// #define MIN 3 // min children

int MAX=5,MIN=3;

typedef struct BTnode *btptr;
typedef struct BTnode
{
    btptr parent;
    int* key; // keeping extra key
    btptr* keyaddr;
    btptr* child;
} btnode;

btptr createnode();
void insert(btptr, int);
void display(btptr);
void displayTree(btptr);
void split_node(btptr);
void merge_node(btptr);
void bubbleSortKeys(int arr[], int n);
void bubbleSortKeysWithChildren(int arr[], int n, btptr childArr[]);
void swap(int *xp, int *yp);
void swapPointers(btptr *x, btptr *y);

btptr root;
int main()
{
    printf("\n...................B-Tree..................");
    int order; 
    printf("\nEnter order of B-Tree : ");
    scanf("%d",&MAX);
    MIN = ceil(MAX/2) + 1;
    printf("\nMAX : %d,MIN : %d",MAX,MIN);
    root = createnode();
    root->parent = root;
    
    // insert(root, 40);
    // insert(root, 20);
    // insert(root, 30);
    // insert(root, 10);
    // insert(root, 8);
    // insert(root, 7);
    // displayTree(root);
    // insert(root, 6);
    // displayTree(root);

    
    int choice,val;
    do{
		printf("\n\nSelect your operation :\n\n1. Insert key\n2. Delete key\n3. Display B-Tree\n0. QUIT\n\nEnter your choice here (0-3) : ");
		scanf("%d",&choice);
		if(choice==1){
			printf("\nEnter the key that you want to insert into B-Tree : ");
			scanf("%d",&val);
			insert(root,val);
		}
		else if(choice == 2){
			printf("\nEnter the number that you want to delete from B-Tree : ");
			scanf("%d",&val);
			// AVL_Delete(root,val);
		}
		else if(choice ==3){
            displayTree(root);
		}
		else if (choice ==0){
			printf("\n\nQuiting...");
			return 0;
		}
	}while(choice!=0);

    return 0;
}


void insert(btptr node, int keyval)
{
    bool childEmpty = true;
    for (int i = 0; i < MAX; i++)
    {
        if (node->child[i] != NULL && keyval < node->key[i])
        {
            insert(node->child[i], keyval);
            childEmpty = false;
            break;
        }
    }
    if (childEmpty)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (node->key[i] == INT_MAX)
            {
                node->key[i] = keyval;
                break;
            }
        }
        bubbleSortKeys(node->key, MAX);
        if (node->key[MAX - 1] != INT_MAX && node->parent == node)
        { // node overflow
            split_node(node);
        }
        else if (node->key[MAX - 1] != INT_MAX && node->parent->key[MAX - 1] == INT_MAX)
        {
            merge_node(node);
            bubbleSortKeysWithChildren(node->parent->key, MAX, node->parent->child);
            if (node->parent->key[MAX - 1] != INT_MAX)
                merge_node(node->parent);
        }
    }
}

void display(btptr root)
{
    for (int i = 0; i < MAX; i++)
        printf("%d ", root->key[i]);
}   

void displayTree(btptr root)
{
    printf("\nroot  ");
    display(root);
    if(root->child[0] != NULL)
        for (int i = 0; i < MAX+1; i++)
        {
            printf("\nchild node %d  : ",i);
            displayTree(root->child[i]);
        }
    printf("\n");
}

btptr createnode()
{
    btptr tmp = (btptr)malloc(sizeof(btnode));
    tmp->key = (int*) malloc(sizeof(int) * MAX);
    tmp->child = (btptr*) malloc(sizeof(btptr) * (MAX+1));
    tmp->keyaddr = (btptr*) malloc(sizeof(btptr) * MAX);
    tmp->parent = NULL;
    int i;
    for (i = 0; i < MAX; i++)
    {
        tmp->key[i] = INT_MAX;
        tmp->keyaddr[i] = NULL;
        tmp->child[i] = NULL;
    }
    tmp->child[i] = NULL;
    return tmp;
}

void split_node(btptr node)
{
    printf("\nsplitNode");

    for (int i = 0; i < MAX + 1; i++)
    {
        (node)->child[i] = createnode();
        (node)->child[i]->parent = (node);
    }
    for (int i = 0; i < MIN - 1; i++)
    {
        (node)->child[0]->key[i] = (node)->key[i];
        (node)->child[1]->key[i] = (node)->key[i + MIN];
    }
    (node)->key[0] = (node)->key[MIN - 1];
    for (int i = 1; i < MAX; i++)
    {
        (node)->key[i] = INT_MAX;
    }
}

void merge_node(btptr node)
{
    printf("\nmergenode");

    int i, j;
    if (node->parent != node)
    {
        for (i = 0; i < MAX + 1; i++)
            if (node->parent->child[i]->key[0] == INT_MAX) // finding first null child
                break;

        for (j = 0; j < MAX; j++)
            if (node->parent->key[j] == INT_MAX) // finding first null key
                break;
    }
    else
    {
        btptr newroot = createnode();
        btptr child = createnode();
        node->parent = newroot;
        newroot->child[0] = node;
        newroot->child[1] = child;
        for (int k = 2; k < MAX + 1; k++)
            newroot->child[k] = createnode();
        for(int k=0; k<=MAX-MIN; k++){
            newroot->child[1]->child[k] = newroot->child[0]->child[k+MIN]; 
            newroot->child[0]->child[k+MIN] = createnode();
        }
        for(int k=MAX-MIN+1; k<MAX+1; k++)
            newroot->child[1]->child[k] = createnode();
        i = 1;
        j = 0;
        root = newroot;
    }

    node->parent->key[j] = node->key[MIN - 1];
    node->key[MIN - 1] = INT_MAX;

    for (int k = 0; k < MAX - MIN; k++)
    {
        node->parent->child[i]->key[k] = node->key[k + MIN];
        node->key[k + MIN] = INT_MAX;
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapPointers(btptr *x, btptr *y)
{
    btptr temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSortKeysWithChildren(int arr[], int n, btptr childArr[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapPointers(&childArr[j + 1], &childArr[j + 2]);
            }
}

void bubbleSortKeys(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}
