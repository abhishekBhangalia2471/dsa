#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct polyTerm * listptr;
typedef struct polyTerm
{
	int exp;
	int coeff;
    listptr next;
} PolyTerm;


listptr front = NULL;
listptr rear = NULL;


void inputPoly(PolyTerm poly[],int size);
void displayPoly(PolyTerm poly[],int size);
void addPoly(listptr poly1, listptr poly2,listptr polySum);
int totalTerms1, totalTerms2,totalTerms3;

int main()
{
    printf("\n.............Polynomial Addition.............");
	printf("\n\nEnter total number of terms in polynomial 1 : ");
	scanf("%d", &totalTerms1);

    //PolyTerm *poly1 = (PolyTerm *)malloc(totalTerms1 * sizeof(PolyTerm));
    //sizeof poly1 will give size of pointer if malloc is used, so using other method of array initiization
    listptr poly1;
	inputPoly(poly1,totalTerms1);

	printf("\n\nEnter total number of terms in polynomial 2 : ");
	scanf("%d", &totalTerms2);
	listptr poly2;
	inputPoly(poly2,totalTerms2);
	
	// PolyTerm* polySum = (PolyTerm *)malloc((totalTerms1 + totalTerms2) * sizeof(PolyTerm));
	listptr polySum;
    polySum->coeff = 0;
    polySum->exp = 0;
    polySum->next = NULL;
	
    printf("\nPolynomial 1 : ");
    displayPoly(poly1,totalTerms1);
    printf("\nPolynomial 2 : ");
    displayPoly(poly2,totalTerms2);
    printf("\nPolynomial 1 + Polynomial 2 : ");
    addPoly(poly1,poly2,polySum);
    displayPoly(polySum,totalTerms3);
    return 0;
}

void inputPoly(listptr poly, int size){
    listptr tmp = (listptr) malloc(sizeof(PolyTerm));
    printf("\n\nElement :\nEnter exponent : ");
    scanf("%d", &tmp->exp);
    printf("Enter coefficient : ");
    scanf("%d", &tmp->coeff);
    tmp->next = NULL;
    // front = tmp;
    poly = front;

    for (int i = 1; i < size; i++)
	{ 
        listptr tmp = (listptr) malloc(sizeof(PolyTerm));
		printf("\n\nElement %d:\nEnter exponent : ",i+1);
		scanf("%d", &tmp->exp);
		printf("Enter coefficient : ");
		scanf("%d", &tmp->coeff);
        tmp->next = NULL;
        rear = tmp;
	}

}

void addPoly(listptr poly1, listptr poly2,listptr polySum){
    
//     int size1 = (*(&poly1 + 1)- poly1)/sizeof(PolyTerm);
//     int size2 = (*(&poly2 + 1)- poly2)/sizeof(PolyTerm);
//     PolyTerm polySum[size1+size2];
//     int size3 = (*(&polySum + 1)- polySum)/sizeof(PolyTerm);

    listptr tmp1 = poly1;
    listptr tmp2 = poly2;
    listptr tmp3 = polySum;

    while (poly1->next != NULL && poly2->next != NULL)
    {
        totalTerms3++;
        if(poly1->exp == poly2->exp){
            listptr tmp = (listptr) malloc(sizeof(PolyTerm));
            tmp->coeff = poly1->coeff + poly2->coeff;
            tmp->exp = poly1->exp;
            tmp->next = NULL;
            polySum->next = tmp;
            polySum = tmp;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        else if (poly1->exp > poly2->exp){
            listptr tmp = (listptr) malloc(sizeof(PolyTerm));
            tmp->coeff = poly1->coeff;
            tmp->exp = poly1->exp;
            tmp->next = NULL;
            polySum->next = tmp;
            polySum = tmp;
            poly1 = poly1->next;
        }
        else {
            listptr tmp = (listptr) malloc(sizeof(PolyTerm));
            tmp->coeff = poly2->coeff;
            tmp->exp = poly2->exp;
            tmp->next = NULL;
            polySum->next = tmp;
            polySum = tmp;
            poly2 = poly2->next;
        }
    }
    

    //for left over terms
    while(poly1->next != NULL){
        listptr tmp = (listptr) malloc(sizeof(PolyTerm));
        tmp->coeff = poly1->coeff;
        tmp->exp = poly1->exp;
        tmp->next = NULL;
        polySum->next = tmp;
        polySum = tmp;
        poly1 = poly1->next;    
    }
    while(poly2->next != NULL){
        listptr tmp = (listptr) malloc(sizeof(PolyTerm));
        tmp->coeff = poly2->coeff;
        tmp->exp = poly2->exp;
        tmp->next = NULL;
        polySum->next = tmp;
        polySum = tmp;
        poly2 = poly2->next;
    }
    poly1 = tmp1;
    poly2 = tmp2;
    polySum = tmp3;
    
}

void displayPoly(listptr poly, int size){
    char sum[100] = "";
	char holder[100];
    int i;

    listptr tmp = poly;


	while(poly->next != NULL)
	{
		sprintf(holder, "%d", poly->coeff);
		strcat(sum, holder);
		strcat(sum, "x^");
		sprintf(holder, "%d", poly->exp);
		strcat(sum, holder);
		strcat(sum, " + ");
        poly = poly->next;
	}
    poly = tmp;
	// sprintf(holder, "%d", poly[i].coeff);
	// strcat(sum, holder);
	// strcat(sum, "x^");
	// sprintf(holder, "%d", poly[i].exp);
	// strcat(sum, holder);
	printf("%s\n",sum);
}
