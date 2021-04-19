#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<phi.h>

int order(int a, int n) {
        /* determines the order of a mod n

           order is defined to be the smallest exponent k >= 1 such that a^k = 1 mod n
        */

        // only coprime numbers have an order mod n
        if (!coprime(a, n)) return 0;

        // pre-compute phi(n)
        int phi_n = phi(n);

        // check order up to phi(n), since by Euler's theorem, phi(n) is the largest order possible mod n
        for (int i = 1; i < phi_n; i++) {
                if (pow(a, i) % n == 1) return i;
        }

        // if we found no order then order is phi(n)
        return phi_n;
}
