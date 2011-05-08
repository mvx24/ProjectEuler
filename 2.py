#!/usr/local/bin/python

import sys

sum = 0
prev = 0
current = 1
next = 1

if len(sys.argv) > 1:
	limit = sys.argv[1]
else:
	limit = 4000000

while next < limit:
	
	# Check for even
	if (next % 2) == 0:
		sum += next
	
	# Calculate next
	next = current + prev
	prev = current
	current = next
	
print sum
