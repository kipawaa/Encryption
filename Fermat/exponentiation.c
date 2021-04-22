#include"exponentiation.h"

int mod_exp(int base, int exp, int mod) {
        int result = base;

        exp %= mod;

        while (exp > 1) {
                result *= base;
                result %= mod;
                exp--;
        }

        return result;
}
