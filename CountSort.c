#include <stdio.h>

void displayArray(int arr[]);
void countSort(int arr[]);
int size, range;

int main(){
    printf("\n.........Count Sort.......");
    printf("\n\nEnter total number of elements in the array : ");
    scanf("%d", &size);
    int arr[size];

    printf("\nEnter the range of elements in the array i.e. if range is 0-9 then type 10 : ");
    scanf("%d",&range);

    printf("\nEnter elements of array : \n");
    for(int i=0; i<size; i++){
        printf("\nElement %d : ",i+1);
        scanf("%d",&arr[i]);
    }

    printf("\nArray before Count sort : ");
    displayArray(arr);
    printf("\nArray after Count sort : ");
    countSort(arr);
    return 0;
}

void displayArray(int arr[]){
    printf("{ ");
    for(int i=0; i<size; i++){
        printf("%d ",arr[i]);
    }
    printf("}\n");
}

void countSort(int arr[]){
    int count[range];
    int i;

    for(i=0; i<range; i++){
        count[i] = 0;
    }

    for(i=0; i<size; i++){
        count[arr[i]]++;
    }

    int pos[range];
    pos[0]=0;
    for(i=1;i<range;i++){
        pos[i] = pos[i-1]+count[i-1];
    }

    int sortedArray[size];
    for(i=0; i<size; i++){
        sortedArray[pos[arr[i]]++] = arr[i];
    }
    displayArray(sortedArray);
}