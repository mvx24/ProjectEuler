/*
Run a random simulation many times.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int moves[25][5];
const int SEEDS = (1<<5) - 1;

void init_moves() {
	int i, count;
	memset(moves, 0, sizeof(int) * 25 * 5);
	for(i = 0; i <= 25; ++i)
	{
		count = 4;
		if(i <= 4 || i >= 20)
			--count;
		if(i % 5 == 0 || i % 5 == 4)
			--count;
		moves[i][0] = count;
		if(i > 4)
			moves[i][count--] = -5;
		if(i < 20)
			moves[i][count--] = 5;
		if(i % 5 != 0)
			moves[i][count--] = -1;
		if(i % 5 != 4)
			moves[i][count--] = 1;
	}
}

int main(int argc, char *argv[])
{
	int i, position, bottom, top, count, carrying, bit;
	double cma = 0.0;

	init_moves();
	srand(time(NULL));

	for(i = 0; i < 12000000; ++i) {
		top = 0;
		bottom = SEEDS;
		position = 12;
		count = 0;
		carrying = 0;
		while(top != SEEDS) {
			position += moves[position][(random() % moves[position][0]) + 1];
			bit = 1 << (position % 5);
			if(carrying && position <= 4 && !(top & bit)) {
				top |= bit;
				carrying = 0;
			}
			else if(!carrying && position >= 20 && (bottom & bit)) {
				bottom ^= bit;
				carrying = 1;
			}
			++count;
		}
		cma = cma + (((double)count - cma) / (i+1));
	}
	printf("%.7f\n", cma);
	return 0;
}
