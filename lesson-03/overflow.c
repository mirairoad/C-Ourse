#include <stdio.h>
unsigned int a = 0; // global var , unsigned int always positive
signed int b = 0; // global var, signer int always negative
float c = 1.235;
short d = 5000; // max 6784
char e = 128; // 127 max this will print -128
unsigned char f = 256; // 255 max eh eh this will print 0


void incr(int n){
    // int x = 0; // local var
    a = n + 1;
    printf("%d\n", a); // %d digit
}

void decr(int n){
    b = n - 1;
    printf("%d\n", b); //
}

int main(void) {
    incr(a);
    incr(a);
    incr(a);
    incr(a);
    decr(b);
    decr(b);
    decr(b);
    decr(b);
    printf("%f\n", c);
    printf("%d\n", e);
    printf("%d\n", f);
    return 0;
}
