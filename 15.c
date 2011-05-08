/*
There is a pattern in calculating the number of paths
The number of paths is 2 times the number for reaching the neighbor node, vertically or horizontally
because of symmetry..
Each node, left to right has the number of previous paths plus the amount its left neighbor has
n = 1 to 3
e.g.. 1 2 -> 1 3 6 -> 1 4 10 20...
*/

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv)
{
	int64_t array[32] = {1, 2};
	size_t size;
	int i;
	
	for(size = 2; size <= 20; ++size)
	{
		for(i = 1; i < size; ++i)
			array[i] += array[i - 1];
		array[i] = 2 * array[i - 1];
	}
	
	printf("%lld\n", array[i]);
	
	return 0;
}
