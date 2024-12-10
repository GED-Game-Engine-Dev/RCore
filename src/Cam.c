#include <GED/Cam.h>
#include <stdlib.h>
#include <string.h>

ae2f_SHAREDEXPORT
ae2f_err_t GED_CamBuffAll(GED_Cam_t* _this, ae2f_struct ae2f_cBmpSrc* dest, uint32_t background_asRGB) {
    size_t a; ae2f_err_t code = ae2f_errGlob_OK;
    if((code = ae2f_cDsAllocOwnGetSize(_this, &a, 0)) != ae2f_errDsAlloc_NCOPIED)
    goto DONE;

    switch (background_asRGB)
    {
    default: {
        if((code = ae2f_cBmpSrcFill(dest, background_asRGB)) != ae2f_errGlob_OK)
        goto DONE;
    } break;
    case (uint32_t)-1:
        break;
    }

    for(size_t i = 0; i < a; i+=sizeof(struct GED_CamEl)) {
        ae2f_struct GED_CamEl _element;
        if((code = ae2f_cDsAllocOwnGets(
            _this, 
            i, 
            &_element, 
            sizeof(struct GED_CamEl))) != ae2f_errGlob_OK
        ) goto DONE;

        if(!_element.Source.Addr) continue;

        if((code = ae2f_cBmpSrcRectCpy(dest, &_element.Source, &_element.SourceLinked))) // Real
        goto DONE;

        if((code = ae2f_cDsAllocOwnPuts(_this, i, &_element, sizeof(struct GED_CamEl))))
        goto DONE;
    }

    DONE:
    return code;
}

#include <GED/Mig.h>

#if GED_Mig

#undef GED_CamRead
#undef GED_CamWrite
#undef GED_CamMk
#undef GED_CamDel
#undef GED_CamResize

ae2f_SHAREDEXPORT
ae2f_err_t GED_CamResize(GED_Cam_t* _this, size_t count) {
    return ae2f_cDsAllocOwnReSize(_this, count * sizeof(struct GED_CamEl));
}

ae2f_SHAREDEXPORT
ae2f_err_t GED_CamDel(GED_Cam_t* _this) {
    return ae2f_cDsAllocOwnDel(_this);
}

ae2f_SHAREDEXPORT
ae2f_err_t GED_CamMk(GED_Cam_t* _this) {
    return ae2f_cDsAllocOwnInitAuto(_this);
}

ae2f_SHAREDEXPORT
ae2f_err_t GED_CamRead(const GED_Cam_t* _this, struct GED_CamEl* buff, size_t i) {
    return ae2f_cDsAllocOwnGets(_this, i * sizeof(struct GED_CamEl), buff, sizeof(struct GED_CamEl));
}

ae2f_SHAREDEXPORT
ae2f_err_t GED_CamWrite(GED_Cam_t* _this, struct GED_CamEl* buff, size_t i) {
    return ae2f_cDsAllocOwnPuts(_this, i * sizeof(struct GED_CamEl), buff, sizeof(struct GED_CamEl));
}

ae2f_SHAREDEXPORT size_t
GED_CamSize() {
    return sizeof(GED_Cam_t);
}

ae2f_SHAREDEXPORT size_t
GED_CamEl_Size() {
    return sizeof(struct GED_CamEl);
}


ae2f_SHAREDEXPORT ae2f_err_t
GED_CamEl_Init(
    struct GED_CamEl* _this,

    uint8_t Alpha,
    uint8_t ReverseIdx,
    uint32_t WidthAsResized,
    uint32_t HeightAsResized,
    uint32_t AddrXForDest,
    uint32_t AddrYForDest,
    uint32_t DataToIgnore,

    const struct ae2f_cBmpSrc* bitmapsource
) {
    if(!(_this && bitmapsource)) 
    return ae2f_errGlob_PTR_IS_NULL;

    _this->SourceLinked = (struct ae2f_cBmpSrcRectCpyPrm) {
        .AddrDest.x = AddrXForDest,
        .AddrDest.y = AddrYForDest,
        .DataToIgnore = DataToIgnore,
        .Alpha = Alpha,
        .Resz.x = WidthAsResized,
        .Resz.y = HeightAsResized,

        .ReverseIdx = ReverseIdx,

        .ReverseIdx = 0
    };

    _this->Source = bitmapsource[0];
    return ae2f_errGlob_OK;
}

ae2f_SHAREDEXPORT ae2f_err_t
GED_CamEl_getParam(struct GED_CamEl* _this, struct ae2f_cBmpSrcRectCpyPrm** param) {
    if(!(_this && param)) return ae2f_errGlob_PTR_IS_NULL;
    param[0] = &_this->SourceLinked;
    return ae2f_errGlob_OK;
}

#endif