#!/usr/bin/python

from math import *

num = str(factorial(100))
sum = 0
for digit in num:
	sum += int(digit)
print sum
