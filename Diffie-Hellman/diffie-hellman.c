#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"primitive_roots.h"
#include"primes.h"


// takes a public modulus p and returns a primitive root which is the public base
int get_public_base(int p) {
        // start with a random number mod p
        int root = rand() % p;
        
        // move forwards until finding a primitive root mod p
        // recall that every prime has at least one primitive root, so this WILL end
        while (!is_primitive_root(root, p)) {
                root++;
        }

        return root;
}


int main() {
        // seed RNG
        srand(time(NULL));

        int mod = get_prime(1000);
        
        int base = get_public_base(mod);

        printf("modulus: %d, base: %d\n", mod, base);
        
}
