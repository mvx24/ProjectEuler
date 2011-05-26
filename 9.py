#!/usr/bin/python

def test(a,b,c):
	if ((a*a) + (b*b)) != (c*c):
		return False
	return True

# exhaustive search
for c in reversed(range(1,1000)):
	for b in reversed(range(1,1000 - c)):
		a = 1000 - (b + c)
		if test(a,b,c):
			print "a: %d, b: %d, c: %d" % (a,b,c)
			print "product: %d" % (a*b*c)
			exit()
