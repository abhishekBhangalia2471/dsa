#include <stdio.h>
// #include <limits.h>
#include <float.h>
#include <stdlib.h>

typedef struct Node* nodeptr;
typedef struct Node{
    float val;
    nodeptr next;
}node;

nodeptr SortedMerge(nodeptr left, nodeptr right);
void SplitList(nodeptr head, nodeptr* left, nodeptr* right);
void MergeSort(nodeptr* bucketHead);

int main(){
    float min, max;
    max = FLT_MIN;
    min = FLT_MAX;
    
    int size;
    printf("enter size : ");
    scanf("%d",&size);
    nodeptr* bucket = (nodeptr*)malloc(sizeof(nodeptr) * size);
    
    float A[size];
    for(int i=0;i<size;i++)
   	    bucket[i] = NULL;
    
    for(int i=0; i<size; i++){
        scanf("%f",&A[i]);
        if(A[i] > max)
            max = A[i];
        if (A[i] < min)
            min = A[i];   
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
        nodeptr temp = (nodeptr) malloc(sizeof(node));
        temp->val = A[i];
        temp->next  = bucket[k];
        bucket[k] = temp;
    }
    
    //printing buckets
    printf("\nBuckets :\n");
    for(int i=0;i<size;i++){
    	nodeptr tmp = bucket[i];
    	printf("\nBucket %d : ",i);
    	while(tmp){
    		printf("%f ",tmp->val);
    		tmp=tmp->next;
    	};
    	printf("\n");
    }
    
    //sorting each bucket
    for(int i=0; i<size; i++){
        MergeSort(&bucket[i]);
    }

    //printing sorted elements
    printf("\nElements after Bucket Sort : ");
    for(int i=0; i<size; i++){
        nodeptr tmp = bucket[i];
        while(tmp){
            printf("%f ",tmp->val);
            tmp = tmp->next;
        }
    }
    printf("\n");
    return 0;
}

void MergeSort(nodeptr* bucketHead){
    nodeptr head = *bucketHead;
    nodeptr left;
    nodeptr right;

    //base case : lenght 0 or 1
    if (head == NULL || head->next == NULL)
        return;
    SplitList(head,&left,&right);
    MergeSort(&left);
    MergeSort(&right);
    *bucketHead = SortedMerge(left,right);
}

void SplitList(nodeptr head, nodeptr* left, nodeptr* right){
    nodeptr fast, slow;
    slow = head;
    fast = head->next;

    while(fast != NULL){
        fast = fast->next;
        if(fast!=NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

nodeptr SortedMerge(nodeptr left, nodeptr right){
    nodeptr result = NULL;
    if(left == NULL)
        return right;
    if(right == NULL)
        return left;
    if (left->val <= right->val){
        result = left;
        result->next = SortedMerge(left->next,right);
    }
    else{
        result = right;
        result->next = SortedMerge(left,right->next);
    }
    return result;
}