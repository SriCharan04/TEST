#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

//OpenCL program to perform vector addition of two arrays.
const char* programSource = 
"__kernal                                   \n"
"void vecadd(__global int *A,               \n"
"            __global int *B,               \n"
"            __global int *C,)              \n"
"{                                          \n"
"//Get the work-item's unique ID            \n"                                 
"int idx = get_global_id(0);                \n"
"//Add the corresponding locations of       \n"
"//'A' and 'B' and store the result in 'C'  \n"
"C[idx] = A[idx]+B[idx];                    \n"
"}                                          \n";

int main()
{
    // This code executes on OpenCL host
    //Host data

    int *A = NULL;
    int *B = NULL;
    int *C = NULL;

    //Elements in each array
    const int elements = 2048;

    //Datasize computation
    size_t datasize = sizeof(int) *elements;

    //Allocate Input/Output data space
    A = (int*)malloc(datasize);
    B = (int*)malloc(datasize);
    C = (int*)malloc(datasize);

    //Initialise input data
    for (int i = 0; i < elements; i++)
    {
        A[i] = i;
        B[i] = i;
    }

    //Check output of each API call
    cl_int status;

    //_________________________________________
    //STEP 1: Discover and initialise platforms
    //_________________________________________
    cl_uint numPlatforms = 0;
    cl_platform_id *platforms = NULL;

    //Retrieve number of platforms
    status = clGetPlatformIDs(0,NULL,&numPlatforms);

    //Allocate enough space for each platform
    platforms = (cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));

    //Fill in platforms
    status = clGetPlatformIDs(numPlatforms,platforms,NULL);

    //_________________________________________
    //STEP 2: Discover and initialise devices
    //_________________________________________
    cl_uint numDevices = 0;
    cl_device_id *devices = NULL;

    //Retrieve number of present devices
    status = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_ALL,0,NULL,&numDevices);
    devices = (cl_device_id*)malloc(numDevices*sizeof(cl_device_id));

    //Fill devices 
    status = clGetDeviceIDs(platforms[0],CL_DEVICE_TYPE_ALL,numDevices,devices,NULL);

    //_________________________________________
    //STEP 3: Create a context
    //_________________________________________
    cl_context context = NULL;
    context = clCreateContext(NULL,numDevices,devices,NULL,NULL,&status);

    //_________________________________________
    //STEP 4: Create a command queue
    //_________________________________________
    cl_command_queue cmdQueue;
    cmdQueue = clCreateCommandQueue(context,devices[0],0,&status);

    //_________________________________________
    //STEP 5: Create device buffers
    //_________________________________________
    cl_mem bufferA; //Input array on device
    cl_mem bufferB; //Input array on device
    cl_mem bufferC; //Output array on device

    //Create buffer object containing data from host array A
    bufferA = clCreateBuffer(context,CL_MEM_READ_ONLY,datasize,NULL,&status);

    //Create buffer object containing data from host array B
    bufferB = clCreateBuffer(context,CL_MEM_READ_ONLY,datasize,NULL,&status);

    //Create buffer object to hold output data
    bufferC = clCreateBuffer(context,CL_MEM_WRITE_ONLY,datasize,NULL,&status);

    //_________________________________________
    //STEP 6: Write host data to device buffers
    //_________________________________________
    
    //Write input array A to buffer A
    status = clEnqueueWriteBuffer(cmdQueue,bufferA,CL_FALSE,0,datasize,A,0,NULL,NULL);

    //Write input array B to buffer B
    status = clEnqueueWriteBuffer(cmdQueue,bufferB,CL_FALSE,0,datasize,B,0,NULL,NULL);

    //_________________________________________
    //STEP 7: Create and compile program
    //_________________________________________

    //Create
    cl_program program = clCreateProgramWithSource(context,1,(const char**)&programSource,NULL,&status);

    //Build
    status = clBuildProgram(program,numDevices,devices,NULL,NULL,NULL);

    //_________________________________________
    //STEP 8: Create the kernel
    //_________________________________________

    cl_kernel kernel = NULL;
    
    //Create a kernal from vector addition "vecadd" function
    kernel = clCreateKernel(program,"vecadd",&status);

    //_________________________________________
    //STEP 9: Set the kernel arguments
    //_________________________________________

    //Associate input and output buffers with kernel
    status = clSetKernelArg(kernel,0,sizeof(cl_mem),&bufferA);
    status = clSetKernelArg(kernel,1,sizeof(cl_mem),&bufferB);
    status = clSetKernelArg(kernel,2,sizeof(cl_mem),&bufferC);

    //_________________________________________
    //STEP 10: Configure the work-item structure
    //_________________________________________

    //Define index space of work items for execution
    size_t globalWorkSize[1];
    globalWorkSize[0] = elements; //There are 'elements' work-items

    //_________________________________________
    //STEP 11: Enqueue the kernel for execution
    //_________________________________________

    //Execute the kernel
    status = clEnqueueNDRangeKernel(cmdQueue,kernel,1,NULL,globalWorkSize,NULL,0,NULL,NULL);

    //_________________________________________
    //STEP 12: Read the output buffer back to the host
    //_________________________________________

    //Read OpenCL output
    clEnqueueReadBuffer(cmdQueue,bufferC,CL_TRUE,0,datasize,C,0,NULL,NULL);

    //Verification
    int result = 1;
    for (int i = 0; i < elements; i++)
    {
        if(C[i]!=i+1)
        {
            result = 0;
            break;
        }
    }
    printf("%d",result);

    //_________________________________________
    //STEP 13: Release OpenCL resources
    //_________________________________________

    //Free OpenCL resources
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(cmdQueue);
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);
    clReleaseContext(context);

    //Free Host resources
    free(A);
    free(B);
    free(C);
    free(platforms);
    free(devices);
}