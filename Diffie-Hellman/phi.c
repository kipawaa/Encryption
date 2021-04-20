#include"phi.h"

int phi(int num) {
        int total = 1;
        
        // current divisor
        int div = 2;

        // until we've found every prime factor of n
        while (num > 1) {
                // if div divides num
                if (num % div == 0) {
                        // determine the multiplicity of div in nums decomposition
                        int power = 1;
                        while (num % (int)pow(div, power + 1) == 0) {
                                power++;
                        }

                        // add phi of that number to the total
                        total *= pow(div, power - 1) * (div - 1);

                        // divide num by that number
                        num /= pow(div, power);
                } else{
                        div += 1;
                }
        }

        return total;
}

