/*
	Ex. 1/7 The long division operations will consist of after the decimal:
	10/7 = 1 (then 10%7 = 3, drop the zero to get 30)
	30/7 = 4 (same steps to get to the next line)
	20/7 = 2
	60/7 = 8
	40/7 = 5
	50/7 = 7
	10/7 <- This dividend(10) was seen before so there's the start of the repeat. cycle length = (current step - 1 - step dividend was seen)
*/

#include <stdio.h>
#include <string.h>

// Do long division of 1.0
int cycle_length(int dividend, int divisor, int *pastDividends, int length)
{
	int dividends[length];
	int result = dividend / divisor;
	int remainder = dividend % divisor;

	if(!remainder) // No cycle found
		return 0;
	
	for(int i = 0; i < (length - 1); ++i)
	{
		if(pastDividends[i] == dividend)
			return length - 1 - i;
	}
	
	if(length > 1) // Lots of copied data, but simplifies the code
		memcpy(dividends, pastDividends, sizeof(int) * (length - 1));
	dividends[length - 1] = dividend;
	return cycle_length(result?remainder*10:dividend*10, divisor, dividends, length + 1);
}

int main(int argc, char *argv[])
{
	int length, bestDivisor, bestLength = 0;
	for(int i = 2; i < 1000; ++i)
	{
		length = cycle_length(10, i, NULL, 1);
		printf("*%d %d\n", i, length);
		if(length > bestLength)
		{
			bestDivisor = i;
			bestLength = length;
		}
	}
	printf("%d: %d\n", bestDivisor, bestLength);
	return 0;
}
