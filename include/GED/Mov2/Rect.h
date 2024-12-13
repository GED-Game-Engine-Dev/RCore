#ifndef GED_Mov_BmpSrcRectPrm_h
#define GED_Mov_BmpSrcRectPrm_h
#include <ae2f/Bmp/Src/Rect.h>
#include <ae2f/mov2/Def.h>

/// @brief
/// A structure type. Use with ae2f_struct. \n
/// @see ae2f_cBmpSrcRectCpyPrm
#define GED_Mov2Prm ae2f_cBmpSrcRectCpyPrm
typedef ae2f_struct GED_Mov2Prm GED_Mov2Prm_t;
typedef ae2f_Mov2RectDef(ae2f_MovScalar_t) GED_Mov2Rect_t;

ae2f_extern ae2f_SHAREDCALL ae2f_Mov2Col_t GED_Mov2PrmColGet(
    const GED_Mov2Prm_t* rect, 
    const ae2f_Mov2Scalar_t* pos
);

ae2f_extern ae2f_SHAREDCALL ae2f_Mov2Col_t GED_Mov2PrmColGetRect(
    const GED_Mov2Prm_t* rect,
    const GED_Mov2Rect_t* tar
);

ae2f_extern ae2f_SHAREDCALL ae2f_Mov2Col_t GED_Mov2PrmColGetPrm(
    const GED_Mov2Prm_t* rect,
    const GED_Mov2Prm_t* prm
);

#endif