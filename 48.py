#!/usr/bin/python

sum = 0
for num in range(1,1001):
	sum += num**num
s = str(sum)
print s[len(s)-10:]
