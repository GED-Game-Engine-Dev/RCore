#include <GED/Camera.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdint.h>

#include <ae2f/BmpCL/BmpCL.h>
struct OpenCLBuff;
static class OpenCL {
    friend OpenCLBuff;
    cl_context ctx = 0;
    cl_device_id device = 0;
    cl_command_queue queue = 0;
    cl_int err = 0;
public:
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

    inline cl_int Cpy(ae2f_cBmpCLBuff* dest, ae2f_cBmpCLBuff* src, const ae2f_cBmpSrcCpyPrm *prm, uint32_t w, uint32_t h) {
        return ae2f_BmpCLCpy(dest, src, prm, queue, w, h);
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

struct OpenCLBuff : public ae2f_cBmpCLBuff {
    inline OpenCLBuff(ae2f_cBmpSrc* p) {
        opencl.err = ae2f_cBmpCLBuffMk(this, CL_MEM_READ_WRITE, p, opencl.ctx, opencl.queue);
    }

    inline ~OpenCLBuff() {
        opencl.err = ae2f_cBmpCLBuffDel(this);
    }
};

#include <ae2f/Ds/Arr.hpp>
#include <ae2f/BitVec.hpp>

ae2f_extern ae2f_SHAREDEXPORT
ae2f_err_t GED_Camera_Buff_Threaded(
    GED_Camera_t* _this,
    ae2f_struct ae2f_cBmpSrc* dest,
    uint32_t background_asRGB,
    uint8_t tdcount
) {
    if(opencl.Check())
    return ae2f_errGlob_IMP_NOT_FOUND;
    OpenCLBuff cldest(dest);
    
    const ae2f::Ds::Arr::cRefer<GED_Camera_El> __this(_this[0]);

    size_t size = 0;
    ae2f_err_t
    err = __this.Length(&size, 0);

    if(err & ae2f_errGlob_DONE_HOWEV) {
        err &= ~ae2f_errGlob_DONE_HOWEV;
    } else return err;

    if(opencl.Fill(
        &cldest, 
        background_asRGB, 
        tdcount, 1)
    ) return ae2f_errGlob_NFOUND;
    
    for(size_t i = 0; i < size; i++) {
        GED_Camera_El el = __this.Read(0, &err);
        OpenCLBuff src(&el.Source);
        if(opencl.Cpy(&cldest, &src, &el.SourceLinked, tdcount, 1)) {
            return ae2f_errGlob_NFOUND;
        }
    }
    
    return err;
}