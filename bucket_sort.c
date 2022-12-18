#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Node{
    float val;
    Node* next;
}node;


int main(){
    float min, max;
    max = FLT_MIN;
    min = FLT_MAX;
    
    int size;
    printf("enter size : ");
    scanf("%d",&size);
    node** bucket = (node**)malloc(sizeof(node*) * 10);
    
    float A[size];
    for(int i=0;i<size;i++){
   	bucket[i] = NULL;
    }
    
    for(int i=0; i<size; i++){
        scanf("%f",&A[i]);
        	if(A[i] > max)
            max = A[i];
        if (A[i] < min){
            min = A[i];
        }
        
    }
    //printf("min %f, max %f",min,max);
    
    float range = max-min;
    
    for(int i=0; i<size; i++){
       // printf("min = %f, range = %f",min,range);
        float b = (A[i] - min)/range;
        int k = b*size;
        //printf("%d",k);
        if(k == size)
        	k--;
        node* temp = (node*) malloc(sizeof(node));
        temp->val = A[i];
        temp->next  = bucket[k];
        bucket[k] = temp;
    }
    
    for(int i=0;i<size;i++){
    	node* tmp = bucket[i];
    	printf("\nBucket %d : ",i);
    	while(tmp){
    		printf("%f ",tmp->val);
    		tmp=tmp->next;
    	};
    	printf("\n");
    }
    
    
}