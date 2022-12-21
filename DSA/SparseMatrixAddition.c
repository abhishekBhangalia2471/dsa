#include <stdio.h>
#include <stdlib.h>

typedef struct MatrixNode{
	int row;
	int column;
	int value;
} matrixNode;

void addMatrices(matrixNode m1[], matrixNode m2[], matrixNode mSum[]);
void displayMatrix(matrixNode m[],int size);
void inputMatrix(matrixNode m[], int size);

int totalTerms1, totalTerms2,totalTerms3=0;


int main()
{
	
    printf("\n.............Matrix Addition.............");

	printf("\n\nEnter total number of terms in matrix 1 : ");
	scanf("%d", &totalTerms1);
    matrixNode matrix1[totalTerms1];
	inputMatrix(matrix1,totalTerms1);

	printf("\n\nEnter total number of terms in matrix 2 : ");
	scanf("%d", &totalTerms2);
	matrixNode matrix2[totalTerms2];
	inputMatrix(matrix2,totalTerms2);
	
	matrixNode matrixSum[totalTerms1+totalTerms2];
    
    printf("\nMatrix 1 : ");
   displayMatrix(matrix1,totalTerms1);
    printf("\n\nMatrix 2 : ");
    displayMatrix(matrix2,totalTerms2);

    printf("\n\nMatrix 1 + Matrix 2 : ");
    addMatrices(matrix1,matrix2,matrixSum);
    displayMatrix(matrixSum,totalTerms3);
    printf("\n");
    return 0;
}


void inputMatrix(matrixNode m[], int size){
	for(int i=0; i<size; i++){
		printf("\n\nElement %d :\nEnter row : ",i+1);
		scanf("%d",&m[i].row);
		printf("\nEnter column : ");
		scanf("%d",&m[i].column);
		printf("\nEnter value : ");
		scanf("%d",&m[i].value);
	}
}

void displayMatrix(matrixNode m[], int size){
	for(int i=0; i<size; i++){
		printf("\nRow : %d, Column : %d, Value : %d",m[i].row,m[i].column,m[i].value);
	}
}

void addMatrices(matrixNode m1[], matrixNode m2[], matrixNode mSum[]){
	int i=0,j=0;
	while(i<totalTerms1 && j<totalTerms2){
		if(m1[i].row == m2[j].row && m1[i].column == m2[i].column){
			mSum[totalTerms3].row = m1[i].row;
			mSum[totalTerms3].column = m1[i].column;
			mSum[totalTerms3++].value = m1[i++].value + m2[j++].value;
		}
		else if (m1[i].row < m2[j].row || m1[i].row == m2[j].row && m1[i].column < m2[j].column){
			mSum[totalTerms3++] = m1[i++];
		}
		else {
			mSum[totalTerms3++] = m2[j++];
		}
	}
	
}
