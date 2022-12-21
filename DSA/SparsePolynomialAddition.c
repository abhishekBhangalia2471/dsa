#include <stdio.h>
#include <string.h>

typedef struct polyTerm
{
	int exp;
	int coeff;
} PolyTerm;

void inputPoly(PolyTerm poly[],int size);
void displayPoly(PolyTerm poly[],int size);
void addPoly(PolyTerm poly1[], PolyTerm poly2[],PolyTerm polySum[]);
int totalTerms1, totalTerms2,totalTerms3;

int main()
{
    printf("\n.............Polynomial Addition.............");
	printf("\n\nEnter total number of terms in polynomial 1 : ");
	scanf("%d", &totalTerms1);

    //PolyTerm *poly1 = (PolyTerm *)malloc(totalTerms1 * sizeof(PolyTerm));
    //sizeof poly1 will give size of pointer if malloc is used, so using other method of array initiization
    PolyTerm poly1[totalTerms1];
	inputPoly(poly1,totalTerms1);

	printf("\n\nEnter total number of terms in polynomial 2 : ");
	scanf("%d", &totalTerms2);
	PolyTerm poly2[totalTerms2];
	inputPoly(poly2,totalTerms2);
	
	// PolyTerm* polySum = (PolyTerm *)malloc((totalTerms1 + totalTerms2) * sizeof(PolyTerm));
	PolyTerm polySum[totalTerms1+totalTerms2];
	
    printf("\nPolynomial 1 : ");
    displayPoly(poly1,totalTerms1);
    printf("\nPolynomial 2 : ");
    displayPoly(poly2,totalTerms2);
    printf("\nPolynomial 1 + Polynomial 2 : ");
    addPoly(poly1,poly2,polySum);
    displayPoly(polySum,totalTerms3);
    return 0;
}

void inputPoly(PolyTerm poly[], int size){
    for (int i = 0; i < size; i++)
	{ 
		printf("\n\nElement %d:\nEnter exponent : ",i+1);
		scanf("%d", &poly[i].exp);
		printf("Enter coefficient : ");
		scanf("%d", &poly[i].coeff);
	}
}

void addPoly(PolyTerm poly1[], PolyTerm poly2[],PolyTerm polySum[]){
    int i,j,k;
    i=0;j=0;k=0;
//     int size1 = (*(&poly1 + 1)- poly1)/sizeof(PolyTerm);
//     int size2 = (*(&poly2 + 1)- poly2)/sizeof(PolyTerm);
//     PolyTerm polySum[size1+size2];
//     int size3 = (*(&polySum + 1)- polySum)/sizeof(PolyTerm);

    while (i<totalTerms1 && j<totalTerms2)
    {
        totalTerms3++;
        if(poly1[i].exp == poly2[j].exp){
            polySum[k].exp = poly1[i].exp;
            polySum[k++].coeff = poly1[i++].coeff + poly2[j++].coeff;
        }
        else if (poly1[i].exp > poly2[j].exp){
            polySum[k++] = poly1[i++];
        }
        else {
            polySum[k++] = poly2[j++];
        }
    }

    //for left over terms
    while(i<totalTerms1){
        totalTerms3++;        
        polySum[k++] = poly1[i++];
    }
    while(j<totalTerms2){
        totalTerms3++;
        polySum[k++] = poly2[j++];
    }
    
}

void displayPoly(PolyTerm poly[], int size){
    char sum[100] = "";
	char holder[100];
    int i;
	for (i = 0; i < size - 1 ; i++)
	{
		sprintf(holder, "%d", poly[i].coeff);
		strcat(sum, holder);
		strcat(sum, "x^");
		sprintf(holder, "%d", poly[i].exp);
		strcat(sum, holder);
		strcat(sum, " + ");
	}
	sprintf(holder, "%d", poly[i].coeff);
	strcat(sum, holder);
	strcat(sum, "x^");
	sprintf(holder, "%d", poly[i].exp);
	strcat(sum, holder);
	printf("%s\n",sum);
}
