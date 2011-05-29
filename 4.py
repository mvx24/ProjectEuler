#!/usr/bin/python

largestTuple = ()
largestProduct = 0

def test(x):
	str = "%d" % (x,)
	i = 0
	while i < len(str)/2:
		if str[i] != str[len(str) - (i + 1)]:
			return False
		i += 1
	return True

for a in reversed(range(100,999)):
	for b in reversed(range(100,999)):
		if test(a*b):
			if largestProduct < (a*b):
				largestProduct = (a*b)
				largestTuple = (a,b)

print largestProduct				
print largestTuple
