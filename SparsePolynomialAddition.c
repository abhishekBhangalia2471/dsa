#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct polyTerm
{
	int exp;
	int coeff;
} PolyTerm;

void inputPoly(PolyTerm* poly);
void displayPoly(PolyTerm poly[]);
PolyTerm* addPoly(PolyTerm poly1[], PolyTerm poly2[]);

int main(int argc, char *argv[])
{
	int totalTerms1, totalTerms2;
    printf("\n.............Polynomial Addition.............");

	printf("\n\nEnter total number of terms in polynomial 1 : ");
	scanf("%d", &totalTerms1);
	// PolyTerm *poly1 = (PolyTerm *)malloc(totalTerms1 * sizeof(PolyTerm));
    PolyTerm poly1[totalTerms1];
   // printf("%d %d main",sizeof(poly1),sizeof(poly1[0]));
	inputPoly(poly1);

	printf("Enter total number of terms in polynomial 2 : ");
	scanf("%d", &totalTerms2);
	PolyTerm poly2[totalTerms2];
	inputPoly(poly2);

	PolyTerm* polySum = (PolyTerm *)malloc((totalTerms1 + totalTerms2) * sizeof(PolyTerm));
	// int k = 0;
	// for (int i = 0; i < totalTerms1; i++)
	// {
	// 	for (int j = 0; j < totalTerms2; j++)
	// 	{
	// 		if (poly1[i].exp == poly2[j].exp)
	// 		{
	// 			polySum[k].exp = poly1[i].exp;
	// 			polySum[k++].coeff = poly1[i].coeff + poly2[j].coeff;
	// 		}
	// 	}
	// }
    
    printf("Polynomial 1 : ");
    displayPoly(poly1);
    printf("Polynomial 1 : ");
    displayPoly(poly2);

    printf("Polynomial 1 + Polynomial 2 : ");
    polySum = addPoly(poly1,poly2);
    displayPoly(polySum);
}

void inputPoly(PolyTerm* poly){
    printf("%d %d %d %d",sizeof(poly),sizeof(poly[0]),*(&poly + 1)- poly,sizeof(PolyTerm));

    for (int i = 0; i < sizeof(&poly)/sizeof(PolyTerm); i++)
	{ 
		printf("\n\nElement %d:\nEnter exponent : ",i+1);
		scanf("%d", &poly[i].exp);
		printf("Enter coefficient : ");
		scanf("%d", &poly[i].coeff);
	}
}


PolyTerm* addPoly(PolyTerm poly1[], PolyTerm poly2[]){
    int i,j,k;
    i=0;j=0;k=0;
    PolyTerm* polySum = (PolyTerm*) malloc((sizeof(poly1)+sizeof(poly2)));

    while (i<sizeof(poly1)/sizeof(PolyTerm) && j<sizeof(poly2)/sizeof(PolyTerm))
    {
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
    while(i<sizeof(poly1) / sizeof(PolyTerm)){
        polySum[k++] = poly1[i++];
    }
    while(j<sizeof(poly2) / sizeof(PolyTerm)){
        polySum[k++] = poly2[j++];
    }
    return polySum;
}

void displayPoly(PolyTerm poly[]){
    char sum[] = "";
	char holder[10];
    int i;
	for (i = 0; i < (sizeof(poly) / sizeof(PolyTerm)) - 1; i++)
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
	printf(sum);
}