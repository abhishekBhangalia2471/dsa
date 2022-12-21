#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define MIN 3

typedef struct Btnode *Btreeptr;
typedef struct Btnode{
    Btreeptr parent;
    int key[MAX];                   // keeping extra key 
    Btreeptr keyaddress[MAX];
    Btreeptr child[MAX +1]
}btreenode;

Btreeptr createnode();
void insert(Btreeptr,int);
void display(Btreeptr);
void fulldisplay(Btreeptr);
void spiltnode(Btreeptr);
void upperspiltnode(Btreeptr);

int main(){
    Btreeptr dumy = createnode();
    // putting random address  latter used this to check parent != NULL
    // to avoid segmentation error
    dumy->parent = dumy;

    insert(dumy,20);
    insert(dumy,40);
    insert(dumy,60);
    insert(dumy,80);
    display(dumy);
    printf("\n inserting 100 it will split root node");
    insert(dumy,100);
    
    fulldisplay(dumy);
    printf("\n inserting 50 55 ");
    insert(dumy,50);
     insert(dumy,55);
     fulldisplay(dumy);
     printf("\n inserting 120 125");
     insert(dumy,120);
     insert(dumy,125);
     fulldisplay(dumy);
     printf("\n inserting 140 it will call upper spilt");
     insert(dumy,140);
     fulldisplay(dumy);
      printf("\n inserting 110 115");
     insert(dumy,110);
      insert(dumy,115);
       insert(dumy,116);
        insert(dumy,117);
         insert(dumy,118);
          insert(dumy,119);
     fulldisplay(dumy);

    return 0;
    
}
void insert(Btreeptr node,int keyval){
    
    if(node->child[0] != NULL &&  keyval < node->key[0]){
        insert(node->child[0],keyval);
    }                               /// -1
    else if(node->child[1] != NULL && node->key[1] == -1){
        if(keyval > node->key[0]){
        insert(node->child[1],keyval);
        }
    }
    else if(node->child[1] != NULL && node->key[1] != -1){
        if(keyval > node->key[0] && keyval < node->key[1]){
        insert(node->child[1],keyval);
        }
    }
    else if(node->child[2] != NULL && node->key[2] == -1){
        if(keyval > node->key[1]){
        insert(node->child[2],keyval);
        }
    }
    else if(node->child[1] != NULL && node->key[1] != -1){
        /////
        if(keyval > node->key[0] && keyval < node->key[1]){
        insert(node->child[1],keyval);
        }
    }
    else{
         for(int i =0;i<MAX;i++){
            if(node->key[i] == -1){
                node->key[i] = keyval;
                break;
            }
        }       // this condition prevent second spilt at 140
                // for first spilting they point same node
                // not for second spilt
        
        if(node->key[4] != -1 && node->parent->key[4] != -1){
        printf("\n spilt b tree called");
        spiltnode(node);
        }
        else if(node->key[4] != -1 && node->parent->key[4] == -1){
           printf("\n upper spilt b tree called");
           upperspiltnode(node);
        }
        
        
       
       
    }
}
void display(Btreeptr root){
    for(int i=0;i<MAX;i++){
        printf("%d ",root->key[i]);
    }
}
void fulldisplay(Btreeptr root){
    printf("\nroot  ");
    display(root);
    for(int i=0;i<MAX;i++){
        printf("\nchild node  ");
        printf("%d  ", i);
        display(root->child[i]);
    }
}
Btreeptr createnode(){
     Btreeptr btnode = (Btreeptr)malloc(sizeof(btreenode));
     btnode->parent = NULL;
     for(int i =0;i<MAX;i++){
        btnode->key[i] = -1;
        btnode->keyaddress[i] = NULL;
        btnode->child[i] = NULL;
    }
    return btnode;
}
void spiltnode(Btreeptr node){
    printf("\n i am spilt");

    for(int i =0;i<MAX +1;i++){
         node->child[i] = createnode();
         node->child[i]->parent = node;
    }
    
    node->child[0]->key[0] =node->key[0];
    node->child[0]->key[1] =node->key[1];
    node->key[0] = node->key[2];
    node->child[1]->key[0] =node->key[3];
    node->child[1]->key[1] =node->key[4];
        
    for(int i=1;i<MAX;i++){
        node->key[i] = -1;
    }
    
}
void upperspiltnode(Btreeptr node){
     printf("\n i am upper spilt");
     // used for to identitfy next empty node 
     // as all node create at same time 
     // they have contionous allocation
     // check by running example
     int i =0;
     for(i = 0;i<MAX;i++){
          if(node->parent->child[i]->key[1] == -1){
              break;
          }
     }
     int j =0;
     for(j=0;j<MAX;j++){
         if(node->parent->key[j] == -1){
              break;
          }
     }
     // after both loop we have value of i and j
     node->parent->key[j] = node->key[2];
     node->key[2] = -1;
     // run loop 2 times 
     for(int k =0;k<MAX -MIN;k++){
         node->parent->child[i]->key[k] = node->key[k+MIN];
         node->key[k+MIN] = -1;
     }
     
}