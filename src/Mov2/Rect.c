#include <GED/Mov2/Rect.h>

#define axis_t ae2f_MovVec_t

static ae2f_Mov2DotRotDef(ae2f_MovScalar_t, axis_t);
static ae2f_Mov2RectColGetDef(ae2f_MovScalar_t);
static ae2f_Mov2RectRotColGetDef(ae2f_MovScalar_t, axis_t);

ae2f_SHAREDEXPORT ae2f_err_t GED_Mov2PrmGetCentre(
    const ae2f_struct GED_Mov2Prm* _this,
    ae2f_Mov2Scalar_t* out
) {
    if(!(_this && out)) return ae2f_errGlob_PTR_IS_NULL;

    out->x =  _this->AddrDest.x + (_this->Resz.x >> 1),
    out->y =  _this->AddrDest.y + (_this->Resz.y >> 1);

    return ae2f_Mov2DotRotDefName(ae2f_MovScalar_t, ae2f_MovVec_t)(
        out, &_this->Axis, _this->RotateXYCounterClockWise
    );
}

ae2f_SHAREDEXPORT ae2f_err_t GED_Mov2PrmSetCentre(
    ae2f_struct GED_Mov2Prm* _this,
    const ae2f_Mov2Scalar_t* in_ptr
) {
    if(!(_this && in_ptr)) return ae2f_errGlob_PTR_IS_NULL;

    _this->AddrDest = in_ptr[0];

    ae2f_err_t err;

    err = ae2f_Mov2DotRotDefName(ae2f_MovScalar_t, ae2f_MovVec_t)(
        &_this->AddrDest, &_this->Axis, -_this->RotateXYCounterClockWise
    );

    _this->AddrDest.x -= _this->Resz.x >> 1;
    _this->AddrDest.y -= _this->Resz.y >> 1;

    return err;
}

ae2f_SHAREDEXPORT ae2f_Mov2Col_t GED_Mov2PrmColGet(
    const ae2f_struct GED_Mov2Prm* rect, 
    const ae2f_Mov2Scalar_t* pos
) {
    struct ae2f_Mov2RectDefName(ae2f_MovScalar_t) rect_got = {
        .m = {
            .x = rect->AddrDest.x,
            .y = rect->AddrDest.y
        },

        .M = {
            .x = rect->AddrDest.x,
            .y = rect->AddrDest.y
        }
    };

    rect_got.M.x += rect->Resz.x;
    rect_got.M.y += rect->Resz.y; // x, y done

    return ae2f_Mov2RectRotColGetDefName(ae2f_MovScalar_t, ae2f_MovVec_t)(
        pos, 
        &rect_got, 
        &rect->Axis, 
        rect->RotateXYCounterClockWise
    );
}

ae2f_SHAREDEXPORT ae2f_Mov2Col_t GED_Mov2PrmColGetRect(
    const ae2f_struct GED_Mov2Prm* rect,
    const ae2f_struct ae2f_Mov2RectDefName(ae2f_MovScalar_t)* tar
) {
    ae2f_Mov2Col_t 
    col_m = GED_Mov2PrmColGet(rect, &tar->m),
    col_M = GED_Mov2PrmColGet(rect, &tar->M);

    return col_M & col_m;
}

ae2f_SHAREDEXPORT ae2f_Mov2Col_t GED_Mov2PrmColGetPrm(
    const ae2f_struct GED_Mov2Prm* rect,
    const ae2f_struct GED_Mov2Prm* prm
) {
    ae2f_struct ae2f_Mov2RectDefName(ae2f_MovScalar_t) tar;
    tar.m.x = prm->AddrDest.x;
    tar.m.y = prm->AddrDest.y;
    tar.M.x += prm->Resz.x;
    tar.M.y += prm->Resz.y;

    ae2f_struct ae2f_Mov2RectDefName(ae2f_MovScalar_t) tar2;
    tar2.m.x = tar.m.x;
    tar2.m.y = tar.M.y;

    tar2.M.x = tar.M.x;
    tar2.M.y = tar.m.y;

    #pragma region ____rotate
    #define ___rotate ae2f_Mov2DotRotDefName(ae2f_MovScalar_t, ae2f_MovVec_t)
    ___rotate(
        &tar.m, 
        &prm->Axis, 
        prm->RotateXYCounterClockWise
    );
    ___rotate(
        &tar.M, 
        &prm->Axis, 
        prm->RotateXYCounterClockWise
    );
    ___rotate(
        &tar2.m, 
        &prm->Axis, 
        prm->RotateXYCounterClockWise
    );
    ___rotate(
        &tar2.M, 
        &prm->Axis, 
        prm->RotateXYCounterClockWise
    );
    #undef ___rotate
    #pragma endregion

    ae2f_Mov2Col_t ___rtn;
    ___rtn = GED_Mov2PrmColGet(rect, &tar.M);
    ___rtn &= GED_Mov2PrmColGet(rect, &tar.m);
    ___rtn &= GED_Mov2PrmColGet(rect, &tar2.m);
    ___rtn &= GED_Mov2PrmColGet(rect, &tar2.M);
    return ___rtn;
}