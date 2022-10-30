#include <stdio.h>
#include <stdlib.h>

void push(char c);
char pop();
int size;
char* stack;
int top = 0;

int main(){
    printf("\n........Reverse String using Stack........");
    printf("\n\nEnter total number of characters in the string : ");
    scanf("%d",&size);
    stack = (char *) malloc(size * sizeof(char));
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
    if(top < size){
        stack[top++] = c;
    }
    else {
        printf("\nStack is full !!!");
    }
}

char pop(){
    if (top > 0){
        return stack[--top];
    }
    else {
        return '\0';
    }
}