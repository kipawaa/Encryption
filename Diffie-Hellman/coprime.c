#include"coprime.h"

int max(int a, int b) {
        return a ? a > b : b;
}


int min(int a, int b) {
        return a ? a < b : b;
}


int coprime(int a, int b) {
        /*
           returns 1 if a and b are coprime

           this is done by checking whether the larger number is invertible mod the smaller number,
           which is logically equivalent to being coprime.
        */
        int m = min(a, b);
        int M = max(a, b);

        for (int i = 2; i <= m; i++) {
                if (M % i == 0 && m % i == 0) return 0;
        }

        return 1;
}
