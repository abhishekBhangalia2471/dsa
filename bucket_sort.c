#include <stdio.h>
#include <limits.h>

typedef struct Node{
    float val;
    node* next;
}node;

int main(){
    int min, max;
    max = INT_MIN;
    min = INT_MAX;
    
    int size;
    printf("enter size : ");
    scanf("%d",&size);
    float A[size];
    for(int i=0; i<size; i++){
        cin>>A[i];
        if(A[i] > max)
            max = A[i];
        else if (A[i] < min){
            min = A[i];
        }
    }
    int range = max-min;
    
    for(int i=0; i<size; i++){
        int b = (A[i] - min)/range;
        k = b*size;
        
    }
    
    
}