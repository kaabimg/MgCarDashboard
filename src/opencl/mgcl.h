#ifndef MGCL_H
#define MGCL_H

#include <QtQml>

#include "mgclkernel.h"
#include "mgclenvironment.h"


//#define __NO_STD_VECTOR // Use cl::vector instead of STL version
//#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
#include <string>

#include <iostream>
#include <QDebug>




namespace MgCl {
static void registerQmlTypes()
{
    qmlRegisterType<MgClEnvironment>("MgCl", 1, 0, "MgClEnvironment");
    qmlRegisterType<MgClKernel>("MgCl", 1, 0, "MgClKernel");


//    std::vector<cl::Platform> all_platforms;
//    cl::Platform::get(&all_platforms);

//    qDebug()<<"Platforms count"<<all_platforms.size();

//    for (uint i = 0; i < all_platforms.size(); ++i) {

//        qDebug()<<"=== Platform"<<i<<"information" ;
//        qDebug()<<"CL_PLATFORM_PROFILE"<< all_platforms[i].getInfo<CL_PLATFORM_PROFILE>().c_str();
//        qDebug()<<"CL_PLATFORM_VERSION"<< all_platforms[i].getInfo<CL_PLATFORM_VERSION>().c_str();
//        qDebug()<<"CL_PLATFORM_NAME"<< all_platforms[i].getInfo<CL_PLATFORM_NAME>().c_str();
//        qDebug()<<"CL_PLATFORM_VENDOR"<< all_platforms[i].getInfo<CL_PLATFORM_VENDOR>().c_str();
//        qDebug()<<"CL_PLATFORM_EXTENSIONS"<<all_platforms[i].getInfo<CL_PLATFORM_EXTENSIONS>().c_str();
//    }

//    if(all_platforms.size()==0){
//        qDebug()<<" No platforms found. Check OpenCL installation!";
//        return;
//    }
//    cl::Platform default_platform=all_platforms[0];
//    qDebug()<< "Using platform:"<<default_platform.getInfo<CL_PLATFORM_NAME>().c_str();


//    std::vector<cl::Device> all_devices;
//    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);

//    qDebug()<<"Devices count"<<all_devices.size();
////    cl::Device d;

///*    for (uint i = 0; i < all_devices.size(); ++i) {

//        qDebug()<<"=== Device"<<i<<"information" ;
//        qDebug()<<"CL_DEVICE_TYPE"<< all_devices[i].getInfo<CL_DEVICE_TYPE>();
//        qDebug()<<"CL_DEVICE_VENDOR_ID"<< all_devices[i].getInfo<CL_DEVICE_VENDOR_ID>();
//        qDebug()<<"CL_DEVICE_MAX_COMPUTE_UNITS"<< all_devices[i].getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
//        qDebug()<<"CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS"<< all_devices[i].getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>();
//        qDebug()<<"CL_DEVICE_MAX_WORK_GROUP_SIZE"<< all_devices[i].getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
////        qDebug()<<"CL_DEVICE_MAX_WORK_ITEM_SIZES"<< all_devices[i].getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();

//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR>();
//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT>();
//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT>();
//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG>();
//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT>();
//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE>();
//        qDebug()<<"CL_DEVICE_MAX_CLOCK_FREQUENCY"<< all_devices[i].getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>();
//        qDebug()<<"CL_DEVICE_ADDRESS_BITS"<< all_devices[i].getInfo<CL_DEVICE_ADDRESS_BITS>();
//        qDebug()<<"CL_DEVICE_MAX_READ_IMAGE_ARGS"<< all_devices[i].getInfo<CL_DEVICE_MAX_READ_IMAGE_ARGS>();
//        qDebug()<<"CL_DEVICE_MAX_WRITE_IMAGE_ARGS"<< all_devices[i].getInfo<CL_DEVICE_MAX_WRITE_IMAGE_ARGS>();
//        qDebug()<<"CL_DEVICE_MAX_MEM_ALLOC_SIZE"<< all_devices[i].getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
//        qDebug()<<"CL_DEVICE_IMAGE2D_MAX_WIDTH"<< all_devices[i].getInfo<CL_DEVICE_IMAGE2D_MAX_WIDTH>();
//        qDebug()<<"CL_DEVICE_IMAGE2D_MAX_HEIGHT"<< all_devices[i].getInfo<CL_DEVICE_IMAGE2D_MAX_HEIGHT>();
//        qDebug()<<"CL_DEVICE_IMAGE3D_MAX_WIDTH"<< all_devices[i].getInfo<CL_DEVICE_IMAGE3D_MAX_WIDTH>();
//        qDebug()<<"CL_DEVICE_IMAGE3D_MAX_HEIGHT"<< all_devices[i].getInfo<CL_DEVICE_IMAGE3D_MAX_HEIGHT>();
//        qDebug()<<"CL_DEVICE_IMAGE3D_MAX_DEPTH"<< all_devices[i].getInfo<CL_DEVICE_IMAGE3D_MAX_DEPTH>();
//        qDebug()<<"CL_DEVICE_IMAGE_SUPPORT"<< all_devices[i].getInfo<CL_DEVICE_IMAGE_SUPPORT>();
//        qDebug()<<"CL_DEVICE_MAX_PARAMETER_SIZE"<< all_devices[i].getInfo<CL_DEVICE_MAX_PARAMETER_SIZE>();
//        qDebug()<<"CL_DEVICE_MAX_SAMPLERS"<< all_devices[i].getInfo<CL_DEVICE_MAX_SAMPLERS>();
//        qDebug()<<"CL_DEVICE_MEM_BASE_ADDR_ALIGN"<< all_devices[i].getInfo<CL_DEVICE_MEM_BASE_ADDR_ALIGN>();
//        qDebug()<<"CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE"<< all_devices[i].getInfo<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE>();
//        qDebug()<<"CL_DEVICE_SINGLE_FP_CONFIG"<< all_devices[i].getInfo<CL_DEVICE_SINGLE_FP_CONFIG>();
//        qDebug()<<"CL_DEVICE_GLOBAL_MEM_CACHE_TYPE"<< all_devices[i].getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE>();
//        qDebug()<<"CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE"<< all_devices[i].getInfo<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE>();
//        qDebug()<<"CL_DEVICE_GLOBAL_MEM_CACHE_SIZE"<< all_devices[i].getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE>();
////        qDebug()<<"CL_DEVICE_GLOBAL_MEM_SIZE"<< all_devices[i].getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>().c_str();
//        qDebug()<<"CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE"<< all_devices[i].getInfo<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE>();
//        qDebug()<<"CL_DEVICE_MAX_CONSTANT_ARGS"<< all_devices[i].getInfo<CL_DEVICE_MAX_CONSTANT_ARGS>();
//        qDebug()<<"CL_DEVICE_LOCAL_MEM_TYPE"<< all_devices[i].getInfo<CL_DEVICE_LOCAL_MEM_TYPE>();
//        qDebug()<<"CL_DEVICE_LOCAL_MEM_SIZE"<< all_devices[i].getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();
//        qDebug()<<"CL_DEVICE_ERROR_CORRECTION_SUPPORT"<< all_devices[i].getInfo<CL_DEVICE_ERROR_CORRECTION_SUPPORT>();
//        qDebug()<<"CL_DEVICE_PROFILING_TIMER_RESOLUTION"<< all_devices[i].getInfo<CL_DEVICE_PROFILING_TIMER_RESOLUTION>();
//        qDebug()<<"CL_DEVICE_ENDIAN_LITTLE"<< all_devices[i].getInfo<CL_DEVICE_ENDIAN_LITTLE>();
//        qDebug()<<"CL_DEVICE_AVAILABLE"<< all_devices[i].getInfo<CL_DEVICE_AVAILABLE>();
//        qDebug()<<"CL_DEVICE_COMPILER_AVAILABLE"<< all_devices[i].getInfo<CL_DEVICE_COMPILER_AVAILABLE>();
//        qDebug()<<"CL_DEVICE_EXECUTION_CAPABILITIES"<< all_devices[i].getInfo<CL_DEVICE_EXECUTION_CAPABILITIES>();
//        qDebug()<<"CL_DEVICE_QUEUE_PROPERTIES"<< all_devices[i].getInfo<CL_DEVICE_QUEUE_PROPERTIES>();
//        qDebug()<<"CL_DEVICE_NAME"<< all_devices[i].getInfo<CL_DEVICE_NAME>().c_str();
//        qDebug()<<"CL_DEVICE_VENDOR"<< all_devices[i].getInfo<CL_DEVICE_VENDOR>().c_str();
//        qDebug()<<"CL_DRIVER_VERSION"<< all_devices[i].getInfo<CL_DRIVER_VERSION>().c_str();
//        qDebug()<<"CL_DEVICE_PROFILE"<< all_devices[i].getInfo<CL_DEVICE_PROFILE>().c_str();
//        qDebug()<<"CL_DEVICE_VERSION"<< all_devices[i].getInfo<CL_DEVICE_VERSION>().c_str();
//        qDebug()<<"CL_DEVICE_EXTENSIONS"<< all_devices[i].getInfo<CL_DEVICE_EXTENSIONS>().c_str();
//        qDebug()<<"CL_DEVICE_PLATFORM"<< all_devices[i].getInfo<CL_DEVICE_PLATFORM>();
//        qDebug()<<"CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF"<< all_devices[i].getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF>();
//        qDebug()<<"CL_DEVICE_HOST_UNIFIED_MEMORY"<< all_devices[i].getInfo<CL_DEVICE_HOST_UNIFIED_MEMORY>();
//        qDebug()<<"CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR"<< all_devices[i].getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR>();
//        qDebug()<<"CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT"<< all_devices[i].getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT>();
//        qDebug()<<"CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG"<< all_devices[i].getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_INT>();
//        qDebug()<<"CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT"<< all_devices[i].getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT>();
//        qDebug()<<"CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE"<< all_devices[i].getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE>();
//        qDebug()<<"CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF"<< all_devices[i].getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF>();
////        qDebug()<<"CL_DEVICE_OPENCL_C_VERSION"<< all_devices[i].getInfo<CL_DEVICE_OPENCL_C_VERSION>();
//    }
//*/

//    if(all_devices.size()==0){
//        qDebug()<<" No devices found. Check OpenCL installation!";
//        return;
//    }

//    std::vector<cl::Device>  default_device;
//    default_device.push_back(all_devices[0]);

//    qDebug()<< "Using device: "<<default_device[0].getInfo<CL_DEVICE_NAME>().c_str();



//    cl::Context context(default_device);

//    qDebug()<<"=== Context information" ;
//    qDebug()<<"CL_CONTEXT_REFERENCE_COUNT"<< context.getInfo<CL_CONTEXT_REFERENCE_COUNT>();
//    qDebug()<<"CL_CONTEXT_DEVICES"<< context.getInfo<CL_CONTEXT_DEVICES>().size();
//    qDebug()<<"CL_CONTEXT_PROPERTIES"<< context.getInfo<CL_CONTEXT_PROPERTIES>().size();
//    qDebug()<<"CL_CONTEXT_NUM_DEVICES"<< context.getInfo<CL_CONTEXT_NUM_DEVICES>();


//    cl::Program::Sources sources;

//    std::string kernel_code=
//            "   void kernel simple_add(global const int* A, global const int* B, global int* C){       "
//            "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 "
//            "   }                                                                               ";

//    sources.push_back(std::make_pair(kernel_code.c_str(),kernel_code.length()));

//    cl::Program program(context,sources);
//    if(program.build(default_device)!=CL_SUCCESS){
//        qDebug()<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device[0]).c_str();
//        return;
//    }


//    // create buffers on the device
//    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*10);
//    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);
//    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*10);


//    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};


//    //create queue to which we will push commands for the device.
//    cl::CommandQueue queue(context,default_device[0]);


//    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
//    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);


//    cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);

//    simple_add(buffer_A, buffer_B, buffer_C);
//    int C[10];
//    //read result C from the device to array C
//    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(int)*10,C);

//   qDebug()<<" result: \n";
//    for(int i=0;i<10;i++){
//        qDebug()<<C[i]<<" ";
//    }


}

}



#endif // MGCL_H
