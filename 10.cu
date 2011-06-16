// nvcc -arch=sm_20 10.cu
// Find the sum of all primes below 2 million

#include <stdio.h>
#include <cuda.h>

#define THREADS_PER_BLOCK	512
#define START_NUMBER		1414
#define TOTAL_THREADS		((2000000-START_NUMBER)/2)

__shared__ int blockPrimes[THREADS_PER_BLOCK];

// Kernel that executes on the CUDA device
__global__ void sum_primes(int *firstPrimes, size_t n, unsigned long long *blockSums)
{
	int i;
	int idx;
	int num;
	
	idx = blockIdx.x * blockDim.x + threadIdx.x;
	if(idx < TOTAL_THREADS)
	{
		// The number to test
		num = (START_NUMBER - 1) + (idx * 2);
		for(i = 0; i < n; ++i)
		{
			if(!(num % firstPrimes[i]))
				break;
		}
		if(i == n)
			blockPrimes[threadIdx.x] = num;
		else
			blockPrimes[threadIdx.x] = 0;
	}
	else
	{
		blockPrimes[threadIdx.x] = 0;
	}
	
	__syncthreads();
	
	if(threadIdx.x == 0)
	{
		// sum all the results from the block
		blockSums[blockIdx.x] = 0;
		for(i = 0; i < blockDim.x; ++i)
			blockSums[blockIdx.x] += blockPrimes[i];
	}
}

// main routine that executes on the host
int main(int argc, char *argv[])
{
	//host
	int primes[1024];
	unsigned long long *primeSums;
	int i, j, index;
	int blockSize, nblocks;
	unsigned long long sum;
	size_t len;
	
	//device
	int *primesDevice;
	unsigned long long *primeSumsDevice;
	
	// Find all the primes less than the square root of 2 million ~1414
	primes[0] = 2;
	index = 1;
	sum = 2;
	for(i = 3; i < START_NUMBER; ++i)
	{
		for(j = 0; j < index; ++j)
		{
			if(!(i % primes[j]))
				break;
		}
		if(j == index)
		{
			primes[index++] = i;
			sum += i;
		}
	}
	len = index;
	
	cudaMalloc((void **) &primesDevice, len * sizeof(int));
	cudaMemcpy(primesDevice, primes, len * sizeof(int), cudaMemcpyHostToDevice);
	
	// Test the all odd numbers between 1414 and 2000000
	blockSize = THREADS_PER_BLOCK;
	nblocks = TOTAL_THREADS/blockSize + (TOTAL_THREADS % blockSize?1:0);
	cudaMalloc((void **) &primeSumsDevice, nblocks * sizeof(unsigned long long));
	sum_primes <<< nblocks, blockSize >>> (primesDevice, index, primeSumsDevice);
	
	// Retrieve result from device and store it in host array
	primeSums = (unsigned long long *)malloc(nblocks * sizeof(unsigned long long));
	cudaMemcpy(primeSums, primeSumsDevice, nblocks * sizeof(unsigned long long), cudaMemcpyDeviceToHost);
	for(i = 0; i < nblocks; ++i)
	{
		sum += primeSums[i];
		//printf("%llu\t", primeSums[i]);
	}
	
	// Cleanup
	free(primeSums);
	cudaFree(primeSumsDevice);
	cudaFree(primesDevice);
	
	// Print results
	printf("%llu\n", sum);
}
