#!/usr/bin/python

num = str(2**1000)
sum = 0
for digit in num:
	sum += int(digit)
print sum
