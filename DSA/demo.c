#include <stdio.h>
#include <stdlib.h>

int main(){

    int z = 1;
    // int* p = &x;
    // int* q = p;
    // printf("%d,%d\n",*p,*q);
    // // free(p);
    // *q = 3;
    // q = NULL;
    // printf("\n%d,%d",*p,*q);
    int * y = (int*) malloc(sizeof(int));
    // y = &z;
    *y = 3;
    int * x = (int*) malloc(sizeof(int));
    x = y;
    printf("%d,%d\n",*x,*y);
    *x=4;
    printf("%d,%d\n",*x,*y);
    printf("%p,%p\n",x,y);
    free(y);
    printf("%d,%d\n",*x,*y);
    printf("%p,%p\n",x,y);
    return 0;
}