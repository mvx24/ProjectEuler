#!/usr/bin/python

primenumbers = [2]

def test(a):
	for i in primenumbers:
		if (a % i) == 0:
			return False
	return True

# find each prime number
n = 3
while len(primenumbers) < 10001:
	if test(n):
		primenumbers.append(n)
	n = n + 2

print primenumbers[10000]
