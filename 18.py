#!/usr/bin/python

triangle = [[75],
[95, 64],
[17, 47, 82],
[18, 35, 87, 10],
[20, 04, 82, 47, 65],
[19, 01, 23, 75, 03, 34],
[88, 02, 77, 73, 07, 63, 67],
[99, 65, 04, 28, 06, 16, 70, 92],
[41, 41, 26, 56, 83, 40, 80, 70, 33],
[41, 48, 72, 33, 47, 32, 37, 16, 94, 29],
[53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14],
[70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57],
[91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48],
[63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31],
[04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23]]

# dynamic programming dictionary of answers
maxPaths = {(0,0):75}

# get the max path of the entry at path combined with either the left or right neighbor in the previous row
# path[0] = row, path[1] = column
def getMaxPath(path):
	global maxPaths
	if path not in maxPaths:
		left = right = 0
		if path[1] > 0:
			right = getMaxPath((path[0] - 1, path[1] - 1))
		if path[1] < (len(triangle[path[0]]) - 1):
			left = getMaxPath((path[0] - 1, path[1]))
		
		if left > right:
			maxPaths[path] = triangle[path[0]][path[1]] + left
		else:
			maxPaths[path] = triangle[path[0]][path[1]] + right
	return maxPaths[path]
	
# find the max path for all entries on the bottom row
maxPath = 0
for i in range(len(triangle[len(triangle) - 1])):
	path = getMaxPath((len(triangle) - 1, i))
	if path > maxPath:
		maxPath = path

print maxPath
