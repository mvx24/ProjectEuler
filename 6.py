#!/usr/bin/python

sum = 0
sumSquares = 0

for i in xrange(1,101):
	sum += i
	sumSquares += (i*i)

print (sum * sum) - sumSquares
