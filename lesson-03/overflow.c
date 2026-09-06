#include <stdio.h>

// See README.md sections 2 and 3 for the limits of each type.
unsigned int a = 0; // Unsigned: zero or positive; commonly 0 to 4,294,967,295.
signed int b = 0;   // Signed: negative, zero, or positive; commonly INT_MIN to INT_MAX.
float c = 1.235;    // Stored with limited floating-point precision.
short d = 5000;     // Common limit: -32,768 to 32,767. This value fits.
char e = 128;       // Too large for signed 8-bit char; this system stores -128.
unsigned char f = 256; // One above 255; unsigned conversion wraps to 0.


void incr(int n){
    // See README.md section 4.
    a = n + 1;          // Add one, then store the result in global variable a.
    printf("%d\n", a); // This prints here, but %u is the correct format for a.
}

void decr(int n){
    // See README.md section 5.
    b = n - 1;          // Subtract one, then store the result in global variable b.
    printf("%d\n", b); // %d is the correct format for a signed int.
}

int main(void) {
    // See README.md sections 6 and 7 for these steps and their output.
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
