#include "math_tools.h"

int pgcd(int a, int b){
    /**
    * Computes PGCD between a and b
    **/
    return b ?  pgcd(b,a%b) : a;
}
