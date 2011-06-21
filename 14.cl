__kernel void sequence14(__global int *bestAnswers)
{
	__local int answers[WORK_GROUP_SIZE];
	int i;
	unsigned int n = get_global_id(0);
	
	// Run the sequence
	if(n < WORK_ITEMS)
	{
		i = 1;
		while(n > 1)
		{
			if((n % 2) == 0)
				n = n / 2;
			else
				n = (3 * n) + 1;
			++i;
		}
		answers[get_local_id(0)] = i;
	}
	
	barrier(CLK_LOCAL_MEM_FENCE);
	
	// Find the best sequence in the work group
	if(get_local_id(0) == 0)
	{
		int longestSequence = 0;
		int longestNumber = 0;
		for(i = 0; i < get_local_size(0); ++i)
		{
			if(answers[i] > longestSequence)
			{
				longestSequence = answers[i];
				longestNumber = i;
			}
		}
		bestAnswers[get_group_id(0) * 2] = longestSequence;
		bestAnswers[(get_group_id(0) * 2) + 1] = (WORK_GROUP_SIZE * get_group_id(0)) + longestNumber;
	}
}
