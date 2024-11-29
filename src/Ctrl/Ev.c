#include <GED/Ctrl/Ev.h>
#include <GED/Mig.h>


ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvKill(GED_CtrlEvt* mgr) {
    ae2f_err_t code = ae2f_cDsAllocOwnDel(&mgr->list);
    mgr->wel = 0;
    return code;
}
ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvResize(GED_CtrlEvt* mgr, size_t size) {
    return ae2f_cDsAllocOwnReSize(&mgr->list, ((mgr->wel)) * size);
}
ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvSort(GED_CtrlEvt* mgr, const ae2f_fpCmp_t fpcmp) {
    if(!mgr->wel) return ae2f_errGlob_WRONG_OPERATION;

    return ae2f_cDsArrQSort(ae2f_reinterpret_cast(ae2f_struct ae2f_cDsAllocRef*, &mgr->list), fpcmp, mgr->wel);
}
ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvGetRange(const GED_CtrlEvt* mgr, const GED_fpCtrlEvCond_t fpcond, size_t* Min, size_t* Max) {
    size_t lenbuff; ae2f_err_t code;
    if(!mgr->wel) return ae2f_errGlob_WRONG_OPERATION;

    if((code = ae2f_cDsAllocOwnGetSize(&mgr->list, &lenbuff, 0)) != ae2f_errDsAlloc_NCOPIED)
    return code;

    unsigned found = 0;
    Min[0] = 0;

    char Buff[255];

    for(size_t* i = Min; i[0] < lenbuff / mgr->wel; i[0]++) {

        if((code = ae2f_cDsAllocOwnGets(&mgr->list, i[0] * mgr->wel, Buff, mgr->wel)))
        return code;

        switch (found += fpcond(Buff))
        {
            case 1: {
                Max[0] = i[0];
                i = Max;
            }
            case 2: return ae2f_errGlob_OK;
        }
    }

    switch(found) {
        case 0: return GED_errCtrlEvGetRange_COND_MET_NONE;
        case 1: return GED_errCtrlEvGetRange_COND_MET_ONLY_ONE;
        case 2: return ae2f_errGlob_OK;
    }
}
ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvElement(const GED_CtrlEvt* mgr, size_t i, void* lpEl) {
    return ae2f_cDsAllocOwnGets(&mgr->list, mgr->wel * i, lpEl, mgr->wel);
}
ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvElement_Set(GED_CtrlEvt* mgr, size_t i, const void* lpEl) {
    return ae2f_cDsAllocOwnPuts(&mgr->list, mgr->wel * i, lpEl, mgr->wel);
}
ae2f_SHAREDEXPORT size_t GED_CtrlEvTypeSize() {
    return sizeof(struct GED_CtrlEv);
}
ae2f_SHAREDEXPORT ae2f_err_t GED_CtrlEvMake(GED_CtrlEvt* mgr, uint8_t elsize) {
    if(!elsize) return ae2f_errGlob_WRONG_OPERATION;
    mgr->wel = elsize;
    return ae2f_cDsAllocOwnInitAuto(&mgr->list);
}