#!/usr/local/bin/python

def makeNextPrimeNumber(primeNumberList):
	i = max(primeNumberList)
	length = 1
	while length != 0:
		i += 1
		length = len(filter(lambda x: i % x == 0, primeNumberList))
	primeNumberList.append(i)
	return i

# Do prime factorization, making the prime list bigger as needed

# Seed the prime number list
primeNumberList = [2,3,5,7,11,13,17,19]
primeFactors = []
# Potentially non prime factors
nonPrimeFactors = [600851475143]

while len(nonPrimeFactors):
	nonPrime = nonPrimeFactors[0]
	for prime in primeNumberList:
		if nonPrime % prime == 0:
			# if nonPrime / prime is 1 
			# then the nonPrime number was a prime number all along
			nonPrimeFactors.pop(0)
			if nonPrime / prime != 1:
				nonPrimeFactors.append(nonPrime / prime)
			primeFactors.append(prime)
			break
		elif prime == max(primeNumberList):
			makeNextPrimeNumber(primeNumberList)

#print primeNumberList
print primeFactors
#print nonPrimeFactors
