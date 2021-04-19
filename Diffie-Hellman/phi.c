#include<stdio.h>
#include<stdlib.h>
#include<coprime.h>

int phi(int n) {
        int total = 0;
        for (int i = 1; i < n; i++) {
                total += coprime(i, n); // increments total if i and n are coprime
        }
        return total;
}
