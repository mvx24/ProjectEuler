#!/usr/bin/python

def sequence14(n):
	i = 1
	while n > 1:
		if (n % 2) == 0:
			n = n / 2
		else:
			n = (3 * n) + 1
		i += 1
	return i

largestSequence = 0
largestNumber = 0
for x in range(1000000):
	count = sequence14(x)
	if largestSequence < count:
		largestSequence = count
		largestNumber = x
	
print largestSequence
print largestNumber
 