#include"primitive_roots.h"
#include<stdio.h>

int is_primitive_root(int a, int n) {
        // can't be a primitive root if it's not coprime
        if (!coprime(a, n)) return 0;

        // if it is coprime, then it's a primitive root iff order is phi(n)
        return order(a, n) == phi(n);
}


// takes a public modulus p and returns a primitive root which is the public base
int get_primitive_root(int p) {
        // start with a random number mod p
        int root = rand() % p;

        // move forwards until finding a primitive root mod p
        // recall that every prime has at least one primitive root, so this WILL end
        while (!is_primitive_root(root, p)) {
                root++;
                root %= p;
        }

        return root;
}
