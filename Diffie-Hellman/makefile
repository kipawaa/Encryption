server:
	gcc -Wall -Werror DHKE-server.c primes.c primitive_roots.c order.c phi.c coprime.c exponentiation.c
	time ./a.out
	make clean

client:
	gcc -Wall -Werror DHKE-client.c primes.c primitive_roots.c order.c phi.c coprime.c exponentiation.c
	time ./a.out
	make clean

testing:
	gcc -Wall -Werror testing.c primes.c primitive_roots.c order.c phi.c coprime.c exponentiation.c
	time ./a.out
	make clean

clean:
	rm *.out
