#include <stdio.h>
#include <stdlib.h>
typedef struct matrix{
    int row;
    int col;
    int val;
} SparseMatrixElement;

void FastTransposeSparseMatrix(SparseMatrixElement B[],SparseMatrixElement BT[]);
void displayMatrix(SparseMatrixElement BT[]);
void takeInput(SparseMatrixElement B[]);

int main(){
    SparseMatrixElement B[10],BT[10];
    // B[0].row = 6;
    // B[0].col = 7;
    // B[0].val = 9;
    // B[1].row = 0;
    // B[1].col = 2;
    // B[1].val = 25;
    // B[2].row = 1;
    // B[2].col = 1;
    // B[2].val = 30;
    // B[3].row = 1;
    // B[3].col = 5;
    // B[3].val = 21;
    // B[4].row = 2;
    // B[4].col = 3;
    // B[4].val = 12;
    // B[5].row = 3;
    // B[5].col = 0;
    // B[5].val = 19;
    // B[6].row = 3;
    // B[6].col = 2;
    // B[6].val = 14;
    // B[7].row = 4;
    // B[7].col = 3;
    // B[7].val = 16;
    // B[8].row = 5;
    // B[8].col = 1;
    // B[8].val = 11;
    // B[9].row = 5;
    // B[9].col = 6;
    // B[9].val = 18;

    // printf("Matrix B : \n");
    // displayMatrix(B);
    // FastTransposeSparseMatrix(B,BT);
    // printf("\n\nMatrix BT :\n");
    // displayMatrix(BT);

    takeInput(B);
    printf("Matrix B : \n");
    displayMatrix(B);
    FastTransposeSparseMatrix(B,BT);
    printf("\n\nMatrix BT :\n");
    displayMatrix(BT);
    



}

void displayMatrix(SparseMatrixElement BT[]){
    for(int i=1; i<=BT[0].val; i++){
        printf("row : %d, col : %d, val : %d\n",BT[i].row,BT[i].col,BT[i].val);
    }
}

void takeInput(SparseMatrixElement B[]){
    printf("\nEnter total number of rows : ");
    scanf("%d",&B[0].row);
    printf("\nEnter total number of columns : ");
    scanf("%d",&B[0].col);
    printf("\nEnter Total number of non-zero elements : ");
    scanf("%d",&B[0].val);
    for(int i=1; i<=B[0].val; i++){
        printf("\n\nElement %d:\n",i);
        printf("\nEnter row : ");
        scanf("%d",&B[i].row);
        printf("\nEnter column : ");
        scanf("%d",&B[i].col);
        printf("\nEnter value : ");
        scanf("%d",&B[i].val);
    }
}


void FastTransposeSparseMatrix(SparseMatrixElement B[],SparseMatrixElement BT[]){
    int r,c,n,i,j;
    int *pos, *count;
    r = B[0].row;
    c = B[0].col;
    n = B[0].val;

    pos = (int *) malloc (n * sizeof(int));
    count = (int *) malloc (n * sizeof(int));

    for(int i = 0; i<c; i++){
        count[i] = 0;
    }

    for(int i=1; i<=n; i++){
        count[B[i].col]++;
    }
    pos[0] = 1;

    for(int i=1; i<c; i++){
        pos[i]= pos[i-1] + count[i-1];
    }

    BT[0].row = B[0].col;
    BT[0].col = B[0].row;
    BT[0].val = B[0].val;

    for(int i=1; i<=n; i++){
        j = pos[B[i].col];
        BT[j].row = B[i].col;
        BT[j].col = B[i].row;
        BT[j].val = B[i].val;
        pos[B[i].col]++;
    }

}