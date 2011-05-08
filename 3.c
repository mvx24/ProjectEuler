#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

// Every number has a prime factorization
// So starting from the smallest prime and repeating when possible
// the primes will always be found
int main(int argc, char *argv[])
{
	int64_t number = 600851475143;
	int factor;
	
	for(factor = 2; factor != number; ++factor)
	{
		if(!(number % factor))
		{
			printf("%d\n", factor);
			number /= factor;
			--factor;
		}
	}
	printf("%d\n", factor);
	return 0;
}