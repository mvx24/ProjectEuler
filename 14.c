// gcc -framework OpenCL 14.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define WORK_ITEMS			1000000
#define WORK_GROUP_SIZE		64

#define CheckError(ERROR) do { if(ERROR != CL_SUCCESS) { printf("Line %d: %d\n", __LINE__, ERROR); exit(1); }  } while(0)

cl_device_id clBasicInit(void)
{
	// Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	
	return device_id;
}

int main(int argc, char *argv[])
{
	int i;
	FILE *file;
	struct stat buf;
	char *kernelCode;
	int *answers;
	size_t size, answersSize;
	cl_context context;
	cl_device_id device_id = NULL;
	cl_command_queue command_queue;	
	cl_mem answers_mem_obj;
	cl_program program;
	cl_kernel kernel;
	cl_int ret;
	size_t globalWorkSize, localWorkSize;
	int longestSequence, longestNumber;
	char constants[512];

	file = fopen("14.cl", "r");
	if(!file)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	fstat(fileno(file), &buf);
	kernelCode = (char*)malloc(size = (size_t)buf.st_size);
	fread(kernelCode, 1, size, file);
	fclose(file);
	
	device_id = clBasicInit();
	
	// Create an OpenCL context
	context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	CheckError(ret);
	
	// Create a command queue
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 	CheckError(ret);
 	
	// Create a memory buffer for the solutions
	globalWorkSize = WORK_ITEMS;
	localWorkSize = WORK_GROUP_SIZE;
	answersSize = sizeof(int) * (globalWorkSize/localWorkSize + (globalWorkSize % localWorkSize?1:0)) * 2;
	answers_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, answersSize, NULL, &ret);
	CheckError(ret);

	// Create a program from the kernel source
	program = clCreateProgramWithSource(context, 1, (const char **)&kernelCode, (const size_t *)&size, &ret);
	free(kernelCode);
	CheckError(ret);
	
	// Build the program
	sprintf(constants, "-D WORK_ITEMS=%d -D WORK_GROUP_SIZE=%d", WORK_ITEMS, WORK_GROUP_SIZE);
	ret = clBuildProgram(program, 1, &device_id, constants, NULL, NULL);
	CheckError(ret);
	
	// Create the OpenCL kernel
	kernel = clCreateKernel(program, "sequence14", &ret);
	CheckError(ret);
	
	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&answers_mem_obj);
	CheckError(ret);
	
	// Run the kernel
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
	CheckError(ret);
	
	answers = (int *)malloc(answersSize);
	ret = clEnqueueReadBuffer(command_queue, answers_mem_obj, CL_TRUE, 0, answersSize, answers, 0, NULL, NULL);
	CheckError(ret);
	
	// Find the answer
	longestSequence = longestNumber = 0;
	for(i = 0; i < answersSize/(sizeof(int) * 2); ++i)
	{
		if(longestSequence < answers[i * 2])
		{
			longestSequence = answers[i * 2];
			longestNumber = answers[(i * 2) + 1];
		}
	}
	
	printf("Longest sequence: %d\nLongest Number: %d\n", longestSequence, longestNumber);
	
	// Clean up
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(answers_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(answers);
	return 0;
}
