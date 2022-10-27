#include <stdio.h>

struct polyTerm
{
	int exp;
	int coeff;
};

int main(int argc, char *argv[])
{
	int totalTerms1, totalTerms2;

	printf("Enter total number of terms in polynomial 1 : ");
	scanf("%d", &totalTerms1);
	struct polyTerm *poly1 = (struct polyTerm *)malloc(totalTerms1 * sizeof(struct polyTerm));

	for (int i = 0; i < totalTerms1; i++)
	{
		printf("Enter exponent of term %d : ", i + 1);
		scanf("%d", &poly1[i].exp);
		printf("Enter coefficient of term %d : ", i + 1);
		scanf("%d", &poly1[i].coeff);
	}

	printf("Enter total number of terms in polynomial 2 : ");
	scanf("%d", &totalTerms2);
	struct polyTerm poly2[totalTerms2];

	for (int i = 0; i < totalTerms2; i++)
	{
		printf("Enter exponent of term %d : ", i + 1);
		scanf("%d", &poly2[i].exp);
		printf("Enter coefficient of term %d : ", i + 1);
		scanf("%d", &poly2[i].coeff);
	}

	struct polyTerm *polySum = (struct polyTerm *)malloc((totalTerms1 + totalTerms2) * sizeof(struct polyTerm));

	int k = 0;
	for (int i = 0; i < totalTerms1; i++)
	{
		for (int j = 0; j < totalTerms2; j++)
		{
			if (poly1[i].exp == poly2[j].exp)
			{
				polySum[k].exp = poly1[i].exp;
				polySum[k++].coeff = poly1[i].coeff + poly2[j].coeff;
			}
		}
	}

	char sum[] = "";
	char holder[10];
	for (int i = 0; i < totalTerms1; i++)
	{
		sprintf(holder, "%d", polySum[i].coeff);
		strcat(sum, holder);
		strcat(sum, "x^");
		sprintf(holder, "%d", polySum[i].exp);
		strcat(sum, holder);
		strcat(sum, " + ");
	}
	printf(sum);
}