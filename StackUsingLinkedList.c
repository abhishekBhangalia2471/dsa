#include <stdio.h>
#include <stdlib.h>

typedef struct llnode* listptr;
typedef struct llnode{
    char val;
    listptr next;
}llNode;

void push(char c);
char pop();
int size;
listptr top = NULL;


int main(){
    printf("\n........Reverse String using Stack........");
    printf("\n\nEnter total number of characters in the string : ");
    scanf("%d",&size);
    int i;

    char inputString[size+1];
    for( i=0; i<size; i++){
        printf("\nElement %d : ",i+1);
        scanf("\n%c",&inputString[i]);
        push(inputString[i]);
    }
    inputString[i] = '\0';

    char outputString[size+1];
    for( i=0; i<(size+1); i++){
        outputString[i] = pop();
    }
    
    printf("\nInput String : %s",inputString);
    printf("\nOutput String : %s\n",outputString);
    return 0;
}

void push(char c){
    listptr tmp = (listptr) malloc(sizeof(llNode));
    tmp->val = c;
    tmp->next = top;
    top = tmp;
}

char pop(){
    if (top != NULL){
        char c = top->val;
        top = top->next;
        return c;
    }
    else {
        return '\0';
    }
}