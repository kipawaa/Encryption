#include"primitive_roots.h"
#include<stdio.h>

int is_primitive_root(int a, int n) {
        // can't be a primitive root if it's not coprime
        if (!coprime(a, n)) return 0;

        // if it is coprime, then it's a primitive root iff order is phi(n)
        return order(a, n) == phi(n);
}
