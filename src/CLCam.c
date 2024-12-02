#include <GED/CLPort.h>
#include <GED/Mig.h>
#include <ae2f/Ds/Arr.h>
#include <GED/CLCam.h>

#include <stdio.h>

#undef GED_CLCamRead
#undef GED_CLCamWrite
#undef GED_CLCamMk
#undef GED_CLCamDel
#undef GED_CLCamResize

ae2f_extern ae2f_SHAREDEXPORT ae2f_err_t GED_CLCamBuff(
    GED_CLCam_t* _this, 
    ae2f_struct ae2f_cBmpSrc* dest,
    uint32_t background
) {
    ae2f_err_t code = 0; size_t a = 0;
    if(!(_this && dest))
    return ae2f_errGlob_IMP_NOT_FOUND;

    if((code = ae2f_cDsAllocOwnGetSize(_this, &a, 0)) != ae2f_errDsAlloc_NCOPIED)
    goto DONE;

    ae2f_struct ae2f_cBmpCLBuff cldest;
    ae2f_cBmpCLBuffMk(&cldest, CL_MEM_READ_WRITE, dest, GED_CLCtx);

    switch (background)
    {
    default: {
        ae2f_BmpCLFill(GED_CLQueue, &cldest, background);
    } break;
    case (uint32_t)-1:
        break;
    }

    for(size_t i = 0; i < a; i+=sizeof(struct GED_CLCamEl)) {
        ae2f_struct GED_CLCamEl _element;
        if((code = ae2f_cDsAllocOwnGets(
            _this, 
            i, 
            &_element, 
            sizeof(struct GED_CLCamEl))) != ae2f_errGlob_OK
        ) goto DONE;

        if(!(_element.CLBuff.body && _element.CLBuff.head && _element.CLBuff.source->Addr)) continue;
        if((code = ae2f_BmpCLCpy(GED_CLQueue, &cldest, &_element.CLBuff, _element.Prm))) // Real
        goto DONE;
        if((code = ae2f_cDsAllocOwnPuts(_this, i, &_element, sizeof(struct GED_CLCamEl))))
        goto DONE;
    }

    DONE:
    ae2f_cBmpCLBuffDel(&cldest);
    return code;
}

#if GED_Mig
#undef GED_CLCamMk

ae2f_extern ae2f_SHAREDEXPORT ae2f_err_t GED_CLCamMk(
    GED_CLCam_t* _this
) {
    return ae2f_cDsAllocOwnInitAuto(_this);
}


ae2f_extern ae2f_SHAREDEXPORT ae2f_err_t GED_CLCamRead(
    GED_CLCam_t* _this, 
    ae2f_struct GED_CLCamEl* buff,
    size_t i
) {
    return ae2f_cDsAllocOwnGets(_this, i * sizeof(struct GED_CLCamEl), buff, sizeof(struct GED_CLCamEl));
}

ae2f_extern ae2f_SHAREDEXPORT ae2f_err_t GED_CLCamWrite(
    GED_CLCam_t* _this, 
    ae2f_struct GED_CLCamEl* buff,
    size_t i
) {
    return ae2f_cDsAllocOwnPuts(_this, i * sizeof(struct GED_CLCamEl), buff, sizeof(struct GED_CLCamEl));
}

ae2f_extern ae2f_SHAREDEXPORT ae2f_err_t GED_CLCamDel(
    GED_CLCam_t* _this
) {
    return ae2f_cDsAllocOwnDel(_this);
}

#undef GED_CLCamResize
ae2f_extern ae2f_SHAREDEXPORT ae2f_err_t GED_CLCamResize(
    GED_CLCam_t* _this,
    size_t count
) {
    return ae2f_cDsAllocOwnReSize(_this, count * sizeof(struct GED_CLCamEl));
}

ae2f_extern ae2f_SHAREDEXPORT void GED_CLCamElInit(
    ae2f_struct GED_CLCamEl* el,
    ae2f_struct ae2f_cBmpSrc* src,
    ae2f_struct ae2f_cBmpSrcCpyPrm* prm
) {
    ae2f_cBmpCLBuffMk(&el->CLBuff, CL_MEM_READ_WRITE, src, GED_CLCtx);
    el->Prm[0] = prm[0];
}

ae2f_extern ae2f_SHAREDEXPORT size_t GED_CLCamElSize() {
    return sizeof(ae2f_struct GED_CLCamEl);
}

ae2f_extern ae2f_SHAREDEXPORT void GED_CLCamElDel(ae2f_struct GED_CLCamEl* a) {
    ae2f_cBmpCLBuffDel(&a->CLBuff);
    a->CLBuff.body = a->CLBuff.head = 0;
    a->CLBuff.source = 0;
}

ae2f_SHAREDEXPORT ae2f_err_t 
GED_CLCamElPrm(
    ae2f_struct GED_CLCamEl* a,
    struct ae2f_cBmpSrcCpyPrm** param
) {
    if(!(a && param)) return ae2f_errGlob_PTR_IS_NULL;
    param[0] = a->Prm;
    return ae2f_errGlob_OK;
}

#endif