#include"primes.h"
#include<stdio.h>

// checks if a number is prime
int is_prime(int num) {
        // nothing less than 2 is prime
        if (num < 2) return 0;
        
        // immediately handle even numbers
        if (num % 2 == 0) return 0;
        
        // check all odd numbers in [3, sqrt(n)]
        for (int i = 3; i < sqrt(num) + 1; i += 2) {
                if (num % i == 0) return 0;
        }
        
        return 1;
}


// returns a prime at least as big as min
int get_prime(int min, int max) {
        // make sure things are reasonable
        if (min > RAND_MAX - 1000) return -1;
        if (max < 0) return -1;
        if (max <= min) return -1;
        
        int p = rand();
        p %= max;

        while (p < min || p > max || !is_prime(p)) {
                if (p < min) p = rand();
                else if (p > max) p -= max;
                else if (!is_prime(p)) p++;
        }

        return p;
}
