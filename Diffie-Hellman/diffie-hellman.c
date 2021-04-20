#include"diffie-hellman.h"

// takes a public modulus p and returns a primitive root which is the public base
int get_public_base(int p) {
        printf("start");
        // start with a random number mod p
        int root = rand() % p;

        printf("searching...\n");
        
        // move forwards until finding a primitive root mod p
        // recall that every prime has at least one primitive root, so this WILL end
        while (!is_primitive_root(root, p)) {
                root++;
                printf("trying root: %d\n", root);
        }

        printf("found root %d\n", root);

        return root;
}


int main() {
        printf("seeding\n");
        // seed RNG
        srand(time(NULL));

        printf("getting mod\n");
        int mod = get_prime(1000);
        
        printf("getting base\n");
        int base = get_public_base(mod);

        printf("modulus: %d, base: %d\n", mod, base);
        
}
