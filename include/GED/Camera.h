#if !defined(GED_Camera_h)
#define GED_Camera_h

#include <ae2f/Bmp/Src.h>
#include <ae2f/Ds/Arr.h>

struct GED_Camera_El {
    ae2f_struct ae2f_cBmpSrc Source;
    ae2f_struct ae2f_cBmpSrcCpyPrm SourceLinked;
};

typedef ae2f_struct ae2f_cDsAllocOwn GED_Camera_t;


/// @param This:ae2f_ds_Alloc_Owner 
#define GED_Camera_Init(This) ae2f_ds_Alloc_vOwner_InitAuto(This)

ae2f_SHAREDCALL ae2f_extern ae2f_err_t GED_Camera_BuffAll(GED_Camera_t* _this, ae2f_struct ae2f_cBmpSrc* dest, uint32_t background);

#define GED_Camera_Read(_this, buff, i) ae2f_ds_Alloc_vOwner_Read((_this), (i) * sizeof(struct GED_Camera_El), (buff), sizeof(struct GED_Camera_El))
#define GED_Camera_Write(_this, buff, i) ae2f_ds_Alloc_vOwner_Write((_this), (i) * sizeof(struct GED_Camera_El), (buff), sizeof(struct GED_Camera_El))
#define GED_Camera_Mk ae2f_ds_Alloc_vOwner_InitAuto
#define GED_Camera_Del ae2f_ds_Alloc_vOwner_Del
#define GED_Camera_Resize(_this, count) ae2f_ds_Alloc_vOwner_reSize((_this), (count) * sizeof(struct GED_Camera_El))

#endif