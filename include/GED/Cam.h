#if !defined(GED_Cam_h)
#define GED_Cam_h

#include <ae2f/Bmp/Src/Rect.h>
#include <ae2f/Ds/Arr.h>

struct GED_CamEl {
    ae2f_struct ae2f_cBmpSrc Source;
    ae2f_struct ae2f_cBmpSrcRectCpyPrm SourceLinked;
};

typedef ae2f_struct ae2f_cDsAllocOwn GED_Cam_t;

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CamBuffAll(
    GED_Cam_t* _this, 
    ae2f_struct ae2f_cBmpSrc* dest, 
    uint32_t background
);

#define GED_CamRead(_this, buff, i) ae2f_cDsAllocOwnGets((_this), (i) * sizeof(ae2f_struct GED_CamEl), (buff), sizeof(ae2f_struct GED_CamEl))
#define GED_CamWrite(_this, buff, i) ae2f_cDsAllocOwnPuts((_this), (i) * sizeof(ae2f_struct GED_CamEl), (buff), sizeof(ae2f_struct GED_CamEl))
#define GED_CamMk ae2f_cDsAllocOwnInitAuto
#define GED_CamDel ae2f_cDsAllocOwnDel
#define GED_CamResize(_this, count) ae2f_cDsAllocOwnReSize((_this), (count) * sizeof(ae2f_struct GED_CamEl))

#endif