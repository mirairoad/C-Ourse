#include <stdio.h>  // standard library

int sum(int a, int b){
    return a+b;
}

int main(){

    int a = 5;
    int b, c;

    b=8;

    printf("Hello world %d %d\n",sum(10, 10), 199); // 2 int
    printf("COMBO %d %d\n",a,b); // 2 int, 1 warning GCC will compile and fill out the outputs
    printf("Unassigned %d\n",c); // corrected

    return 0;
}
