#include<stdio.h>
#include<stdlib.h>

#include"coprime.h"
#include"phi.h"
#include"order.h"
#include"primitive_roots.h"
#include"primes.h"
#include"exponentiation.h"


int exponentMessage(int a, int exp, int mod, int expected) {
        int result = mod_exp(a, exp, mod);
        if (result != expected) {
                printf("%d^%d = %d mod %d, but mod_exp gave %d\n", a, exp, expected, mod, result);
                return 0;
        }

        return 1;
}


int testExponentiation(void) {
        if (!exponentMessage(2, 3, 5, 3)) return 0;

        return 1;
}


int testCoprime(void) {
        // make sure 1 is coprime to everything
        for (int i = 1; i < 100; i++) 
                if (!coprime(1, i)) return 0;

        // make sure everything is coprime to primes
        for (int i = 1; i < 7; i++) 
                if (!coprime(i, 7)) return 0;
        
        for (int i = 1; i < 19; i++) 
                if (!coprime(i, 19)) return 0;

        for (int i = 1; i < 1213; i++) 
                if (!coprime(i, 1213)) return 0;
        
        return 1;
}


int testPhi(void) {
        // phi of primes should be p - 1
        if (phi(7) != 6) return 0;
        if (phi(1213) != 1212) return 0;
        if (phi(19139) != 19138) return 0;

        // phi of p^k should be p^{k - 1}(p - 1)
        if (phi(pow(19, 3)) != pow(19, 2) * 18) return 0;
        if (phi(pow(7, 9)) != pow(7, 8) * 6) return 0;

        // check composites
        if (phi(25467) != phi(13) * phi(3) * phi(653)) return 0;
        if (phi(19436) != phi(113) * phi(4) * phi(43)) return 0;

        return 1;
}


int testOrder(void) {
        // test order in the most basic way possible
        for (int i = 1; i < 97; i++) {
                int exp = 1;
                while (mod_exp(i, exp, 97) != 1 && exp < 97) exp++;
                if (exp == 97) exp = 0;
                if (exp != order(i, 97)) {
                        printf("%d failed order: should be %d but got %d\n", i, exp, order(i, 97));
                        return 0;
                }
        }

        printf("passed 97 case\n");

        for (int i = 1; i < 1933; i++) {
                int exp = 1;
                while (mod_exp(i, exp, 1933) != 1 && exp <= 1933) exp++;
                if (exp == 1933) exp = 0;
                if (exp != order(i, 1933)) {
                        printf("%d failed order: should be %d but got %d\n", i, exp, order(i, 1933));
                        return 0;
                }
        }

        // test with a non-prime modulus

        return 1;
}


int testGetPrime(void) {
        int primes[168] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};

        for (int i = 0; i < 1000; i++) {
                int prime = get_prime(0, 1000);
                if (prime < 0 || 1000 < prime) return 0;

                int pass = 0;

                for (int j = 0; j < 168; j++) {
                        if (prime == primes[j]) pass = 1;
                }

                if (!pass) {
                        printf("get_prime said %d was prime, but it's not\n", prime);
                        return 0;
                }
        }

        return 1;
}


int primitiveRootMessage(int root, int mod) {
        if (!is_primitive_root(root, mod)) {
                printf("primitive root said %d was not a primitive root mod %d\n", root, mod);
                return 0;
        }
        return 1;
}


int testIsPrimitiveRoot(void) {
        primitiveRootMessage(17, 1151);
        primitiveRootMessage(3, 25);
        primitiveRootMessage(7, 22);
        primitiveRootMessage(33, 50);

        return 1;
}


int main() {
        if (!testCoprime()) printf("coprime failed tests.\n");
        if (!testPhi()) printf("phi failed tests.\n");
        //if (!testOrder()) printf("order failed tests.\n");
        if (!testGetPrime()) printf("get prime failed tests\n");
        if (!testExponentiation()) printf("exponentiation failed tests\n");
        if (!testIsPrimitiveRoot()) printf("primitive root failed\n");

        printf("testing complete.\n");
}
