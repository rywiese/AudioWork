#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//finds the gcd of x and y using the euclidean algorithm
int gcd(int x, int y) {
    int q = x / y;
    int r = x - q * y;
    if(r == 0)
        return y;
    else
        return gcd(y, r);
}

//finds the lcm of x and y using the fact that
//x * y = gcd(x, y) * lcm(x, y)
int lcm(int x, int y) {
    return (x * y) / gcd(x, y);
}

//simplifies a fraction in place
void fracSimplify(int &num, int &den) {
    int gcd = gcd(num, den);
    num = num / gcd;
    den = den / gcd;
}

//converts a decimal to a fraction
void decToFrac(double r, int &num, int &den) {
    char decString[200];
    snprintf(decString, "%f", r);
    char* s1 = strtok();
}
