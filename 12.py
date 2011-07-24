#!/usr/bin/python

def countDivisors(num):
	count = 0
	for x in range(1, int(num**0.5)):
		if (num % x) == 0:
			count += 2
	return count

num = i = 1
while countDivisors(num) < 500:
	i += 1
	num += i
print "Triangle number: " , num
print "Number of divisors: " , countDivisors(num)
