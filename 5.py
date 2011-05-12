#!/usr/bin/python

"""
The answer can be found by iteratively finding the least common multiple.
Each iteration:
	Do nothing if the current answer is divisible by the number
	If the gcd of the number and the answer is 1, multiply them together
	Else multiply the answer by the number/gcd, or the least common divisor
"""
import fractions

# Find and answer for the 1-20 range of numbers
answer = 1
for i in range(2,21):
	if (answer % i) == 0:
		continue
	divisor = fractions.gcd(i, answer)
	answer *= (divisor == 1) and i or i/divisor
	print "%d: %s" % (i,answer,)
