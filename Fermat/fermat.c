#include"fermat.h"

int fermat(int num, int base) {
        return abs(mod_exp(base, num - 1, num)) == 1;
}


int main() {
        int num;
        int base;
        printf("input a number to test primality: ");
        scanf("%d", &num);
        printf("input a number to witness %d's primality: ", num);
        scanf("%d", &base);

        if (fermat(num, base)) printf("%d is a prime to base %d\n", num, base);
        else printf("%d witnesses that %d is composite\n", base, num);
}
