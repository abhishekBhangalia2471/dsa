#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// order 5
// max keys = 4
// min keys = 2
// max children = 5
// min children = 3
#define MAX 5 // max children
#define MIN 3 // min children

typedef struct Btnode *Btreeptr;
typedef struct Btnode
{
    Btreeptr parent;
    int key[MAX]; // keeping extra key
    Btreeptr keyaddress[MAX];
    Btreeptr child[MAX + 1]
} btreenode;

Btreeptr createnode();
void insert(Btreeptr, int);
void display(Btreeptr);
void fulldisplay(Btreeptr);
void spiltnode(Btreeptr);
void upperspiltnode(Btreeptr);

int main()
{
    Btreeptr dumy = createnode();
    // putting random address  latter used this to check parent != NULL
    // to avoid segmentation error
    dumy->parent = dumy;

    insert(dumy, 20);
    insert(dumy, 40);
    insert(dumy, 60);
    insert(dumy, 80);
    display(dumy);
    printf("\n inserting 100 it will split root node");
    insert(dumy, 100);

    fulldisplay(dumy);
    printf("\n inserting 50 55 ");
    insert(dumy, 50);
    insert(dumy, 55);
    fulldisplay(dumy);
    printf("\n inserting 120 125");
    insert(dumy, 120);
    insert(dumy, 125);
    fulldisplay(dumy);
    printf("\n inserting 140 it will call upper spilt");
    insert(dumy, 140);

    fulldisplay(dumy);
    printf("\n inserting 110 115");
    insert(dumy, 110);
    insert(dumy, 115);
    insert(dumy, 116);
    insert(dumy, 117);
    insert(dumy, 118);
    insert(dumy, 119);
    fulldisplay(dumy);

    return 0;
}
void insert(Btreeptr node, int keyval)
{
    bool childEmpty = false;
    for (int i = 0; i < MAX; i++)
    {
        if (node->child[i] != NULL && node->key[i] != -1 && keyval < node->key[i])
        {
            insert(node->child[i], keyval);
            childEmpty = true;
            break;
        }
        else if (node->child[i] != NULL && node->key[i] == -1 && ((node->key[i - 1] != -1) && (keyval > node->key[i - 1])))
        {
            insert(node->child[i], keyval);
            childEmpty = true;
            break;
        }
    }
    if (!childEmpty)
    {
        for (int i = 0; i < MAX; i++)
        {
            if (node->key[i] == -1)
            {
                node->key[i] = keyval;
                break;
            }
        }
        if (node->key[MAX - 1] != -1 && node->parent->key[MAX - 1] != -1) // node overflow
            spiltnode(node);
        else if (node->key[MAX - 1] != -1 && node->parent->key[MAX - 1] == -1)
            upperspiltnode(node);
    }
}

void display(Btreeptr root)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", root->key[i]);
    }
}
void fulldisplay(Btreeptr root)
{
    printf("\nroot  ");
    display(root);
    for (int i = 0; i < MAX; i++)
    {
        printf("\nchild node  ");
        printf("%d  ", i);
        display(root->child[i]);
    }
}
Btreeptr createnode()
{
    Btreeptr btnode = (Btreeptr)malloc(sizeof(btreenode));
    btnode->parent = NULL;
    for (int i = 0; i < MAX; i++)
    {
        btnode->key[i] = -1;
        btnode->keyaddress[i] = NULL;
        btnode->child[i] = NULL;
    }
    return btnode;
}
void spiltnode(Btreeptr node)
{
    printf("\nsplitNode");

    for (int i = 0; i < MAX + 1; i++)
    {
        node->child[i] = createnode();
        node->child[i]->parent = node;
    }
    for (int i = 0; i < MIN - 1; i++)
    {
        node->child[0]->key[i] = node->key[i];
        node->child[1]->key[i] = node->key[i + MIN];
    }
    node->key[0] = node->key[MIN - 1];
    for (int i = 1; i < MAX; i++)
    {
        node->key[i] = -1;
    }
}
void upperspiltnode(Btreeptr node)
{
    printf("\nuppersplitnode");

    int i = 0;
    for (i = 0; i < MAX + 1; i++)
    {
        if (node->parent->child[i]->key[1] == -1)
        {
            break;
        }
    }
    int j = 0;
    for (j = 0; j < MAX; j++)
    {
        if (node->parent->key[j] == -1)
        {
            break;
        }
    }
    // after both loop we have value of i and j
    node->parent->key[j] = node->key[MIN - 1];
    node->key[MIN - 1] = -1;
    // run loop 2 times

    for (int k = 0; k < MAX - MIN; k++)
    {
        node->parent->child[i]->key[k] = node->key[k + MIN];
        //  printf("\n%d^",node->parent->child[i]->key[k]);
        node->key[k + MIN] = -1;
    }
}