#include <ae2fCL/Bmp/Buff.h>
#include <ae2fCL/Bmp/Bmp.h>

ae2f_SHAREDEXPORT cl_context GED_CLCtx = 0;
ae2f_SHAREDEXPORT cl_command_queue GED_CLQueue = 0;
ae2f_SHAREDEXPORT cl_platform_id GED_CLPlatform = 0;
ae2f_SHAREDEXPORT cl_device_id GED_CLDevice = 0;

ae2f_SHAREDEXPORT ae2f_err_t
GED_CLMk() {
    cl_int err;
    err = clGetPlatformIDs(1, &GED_CLPlatform, 0);
    if(err) return err;
    err = clGetDeviceIDs(GED_CLPlatform, CL_DEVICE_TYPE_GPU, 1, &GED_CLDevice, 0);
    if(err) return err;
    GED_CLCtx = clCreateContext(0, 1, &GED_CLDevice, 0, 0, &err);
    if(err) return err;
    GED_CLQueue = clCreateCommandQueueWithProperties(GED_CLCtx, GED_CLDevice, 0, &err);
    if(err) return err;
    err = ae2fCL_BmpMk(GED_CLCtx, 1, &GED_CLDevice);
    return err;
}

ae2f_SHAREDEXPORT void
GED_CLDel() {
    if(GED_CLCtx) clReleaseContext(GED_CLCtx);
    if(GED_CLDevice) clReleaseDevice(GED_CLDevice);
    if(GED_CLQueue) clReleaseCommandQueue(GED_CLQueue);
    GED_CLCtx = 0; GED_CLDevice = 0; GED_CLQueue = 0;
    ae2fCL_BmpDel();
}

ae2f_SHAREDEXPORT cl_int
GED_CLSrcInit(
    ae2f_struct ae2fCL_cBmpBuff* dest,
    struct ae2f_cBmpSrc* src
) {
    if(!(GED_CLCtx && GED_CLQueue)) return ae2f_errGlob_IMP_NOT_FOUND;
    return ae2fCL_cBmpBuffMk(dest, CL_MEM_READ_WRITE, src, GED_CLCtx);
}
