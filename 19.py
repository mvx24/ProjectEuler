#!/usr/bin/python

days = (31,28,31,30,31,30,31,31,30,31,30,31)

class Date:
	def __init__(self, day, month, year):
		self.day = day - 1
		self.month = month - 1
		self.year = year
		# 0 - Sunday, 1 - Monday, etc.
		self.dayOfWeek = 0
	
	def incrementDay(self):
		self.dayOfWeek += 1
		self.dayOfWeek %= 7
		self.day += 1

		if self.day >= days[self.month]:
			if self.month == 1 and self.day == days[self.month]:
				if self.year % 100 == 0:
					if self.year % 400 == 0:
						return
				elif self.year % 4 == 0:
					return
				# check for leap year
			
			self.day = 0
			self.month += 1
			if self.month == 12:
				self.year += 1
				self.month = 0
		
	def isSundayFirstOfMonth(self):
		return self.dayOfWeek == 0 and self.day == 1
		
	def	__lt__(self, other):
		return other > self
	
	def __gt__(self, other):
		if self.year > other.year:
			return True
		elif self.year == other.year and self.month > other.month:
			return True
		elif self.year == other.year and self.month == other.month and self.day > other.day:
			return True
		return False

	def __str__(self):
		return "%d/%d/%d" % (self.month, self.day, self.year)
	def __unicode__(self):
		return "%d/%d/%d" % (self.month, self.day, self.year)


date = Date(1,1,1900)
date.dayOfWeek = 1
startDate = Date(1,1,1901)
endDate = Date(31,12,2000)

while date < startDate:
	date.incrementDay()

count = 0
while date < endDate:
	if date.isSundayFirstOfMonth():
		count += 1
	date.incrementDay()

print count
