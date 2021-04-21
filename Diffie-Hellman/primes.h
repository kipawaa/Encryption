#include<stdlib.h>
#include<math.h>


/*
   returns a prime at least as big as min and less than max

   min should be at most RAND_MAX - 1000 so that this function can reasonably try to generate above min
*/
int get_prime(int min, int max);
