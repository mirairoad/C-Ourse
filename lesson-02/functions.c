#include <stdio.h>  // See README.md section 7: printf is declared here.

int sum(int a, int b){
    // See README.md sections 3-5 for functions, calls, and the stack pointer.
    return a+b;
}

int main(){

    // See README.md section 6 for the state of these local variables.
    int a = 5;
    int b, c;

    b=8;

    // See README.md section 7 for each placeholder and its value.
    printf("Hello world %d %d\n",sum(10, 10), 199); // Prints 20 and 199.
    printf("COMBO %d %d\n",a,b); // Prints initialized local variables a and b.
    printf("Unassigned %d\n",c); // Warning: reading uninitialized c is undefined behavior.

    return 0;
}
