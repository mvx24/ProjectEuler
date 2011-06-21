#!/usr/bin/python

singles = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
teens = ["eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"]
tens = ["twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"]

# Add up all the single counts
singlesCount = 0
for word in singles:
	singlesCount += len(word)

count = singlesCount + len("ten")
for word in teens:
	count += len(word)

for word in tens:
	count += len(word) * 10
	count += singlesCount

# Multiply the count of 1 to 99 by 10
count *= 10

print count

# Add up all the one hundred words
for word in singles:
	count += len(word) + len("hundred")

# Add up all the one hundred and ... words
for word in singles:
	count += (len(word) + len("hundred") + len("and")) * 99

count += len("onethousand")

print count
