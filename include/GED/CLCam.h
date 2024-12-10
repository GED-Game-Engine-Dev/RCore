#ifndef GED_CLCam_h
#define GED_CLCam_h

#include <ae2fCL/Bmp/Src.h>
#include <ae2f/Ds/Arr.h>
#include "CLPort.h"

struct GED_CLCamEl {
    ae2f_struct ae2f_cBmpCLBuff CLBuff;
    ae2f_struct ae2f_cBmpSrcCpyPrm Prm[1];
};

typedef ae2f_struct ae2f_cDsAllocOwn GED_CLCam_t;

#ifdef __cplusplus
#include "CLCam.hpp"
#endif

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CLCamBuff(
    GED_CLCam_t* _this, 
    ae2f_struct ae2f_cBmpSrc* dest,
    uint32_t background
);

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CLCamRead(
    GED_CLCam_t* _this, 
    ae2f_struct GED_CLCamEl* elbuff,
    size_t i
);

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CLCamWrite(
    GED_CLCam_t* _this, 
    ae2f_struct GED_CLCamEl* elbuff,
    size_t i
);

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CLCamDel(
    GED_CLCam_t* _this
);

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CLCamResize(
    GED_CLCam_t* _this,
    size_t count
);
#define GED_CLCamRead(_this, buff, i) ae2f_cDsAllocOwnGets((_this), (i) * sizeof(ae2f_struct GED_CLCamEl), (buff), sizeof(ae2f_struct GED_CLCamEl))
#define GED_CLCamWrite(_this, buff, i) ae2f_cDsAllocOwnPuts((_this), (i) * sizeof(ae2f_struct GED_CLCamEl), (buff), sizeof(ae2f_struct GED_CLCamEl))
#define GED_CLCamMk ae2f_cDsAllocOwnInitAuto
#define GED_CLCamDel ae2f_cDsAllocOwnDel
#define GED_CLCamResize(_this, count) ae2f_cDsAllocOwnReSize((_this), (count) * sizeof(ae2f_struct GED_CLCamEl))

#endif