#!/usr/bin/python

primenumbers = [2]

def test(a):
	testlimit = int(a**0.5)
	for i in primenumbers:
		if i > testlimit:
			break
		if (a % i) == 0:
			return False
	return True

# find each prime number
n = 3
sum = 2
limit = int(2000000**0.5)
while n < 2000000:
	if test(n):
		if n < limit:
			primenumbers.append(n)
		sum += n
	n = n + 2

print sum
