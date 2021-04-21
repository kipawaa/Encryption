main:
	
	gcc -Wall -Werror diffie-hellman.c primes.c primitive_roots.c order.c phi.c coprime.c exponentiation.c
	time ./a.out
	make clean

testing:
	gcc -Wall -Werror testing.c primes.c primitive_roots.c order.c phi.c coprime.c exponentiation.c
	time ./a.out
	make clean

clean:
	rm *.out
