#include <GED/Camera.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdint.h>

#include <ae2f/BmpCL/BmpCL.h>

class OpenCLBuff {

};

static class OpenCL {
    cl_context ctx = 0;
    cl_device_id device = 0;
    cl_command_queue queue = 0;
public:
    cl_int err = 0;
    inline OpenCL() {
        // OpenCL 초기화
        cl_platform_id platform;
        err = clGetPlatformIDs(1, &platform, NULL);
        if(err != CL_SUCCESS) return;
        ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
        if(err != CL_SUCCESS) return;
        queue = clCreateCommandQueueWithProperties(ctx, device, 0, &err);
        if(err != CL_SUCCESS) return;
        err = ae2f_BmpCLMk(ctx, 1, &device);
        if(err != CL_SUCCESS) return;        
    }

    inline cl_int Fill(ae2f_cBmpCLBuff* dest, uint32_t colour, uint32_t w, uint32_t h) {
        return ae2f_BmpCLFill(dest, queue, colour, w, h);
    }

    inline cl_int Cpy() {
        return ae2f_BmpCL
    }

    constexpr bool Check() {
        return err;
    }

    inline ~OpenCL() {
        clReleaseContext(ctx);
        clReleaseCommandQueue(queue);
        clReleaseDevice(device);
        ae2f_BmpCLDel();
    }
} opencl;

ae2f_extern ae2f_SHAREDEXPORT
ae2f_err_t GED_Camera_Buff_Threaded(
    GED_Camera_t* _this,
    ae2f_struct ae2f_cBmpSrc* dest,
    uint32_t background_asRGB,
    uint8_t tdcount
) {
    if(opencl.Check()) 
    return ae2f_errGlob_IMP_NOT_FOUND;

}