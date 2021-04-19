#include<math.h>
#include<stdlib.h>

// checks if a number is prime
int is_prime(int n) {
        // nothing less than 2 is prime
        if (num < 2) return 0;
        
        // 2 is the only even prime, so special case
        if (num == 2) return 1;
        
        // check all odd numbers in [3, sqrt(n)]
        for (int i = 3; i < ceil(sqrt(n)); i += 2) {
                if (n % i == 0) return 0;
        }
        
        return 1;
}


// returns a prime at least as big as min
int get_prime(int min) {
        // make sure things are reasonable
        if (min > RAND_MAX - 1000) return -1;
        
        int p = rand();

        while (p < min){
                p += rand();
        }

        while (!is_prime(p)) p++;

        return p;
}
