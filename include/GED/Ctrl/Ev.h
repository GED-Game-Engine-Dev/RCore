#if !defined(GED_Ctrl_Ev_h)
#define GED_Ctrl_Ev_h
#include <ae2f/Ds/Arr.h>
#include <ae2f/Cast.h>
#include <ae2f/Call.h>
#include <stdint.h>

// inside is Allocator::cOwner. (aka ae2f_ds_Alloc_Owner)
typedef struct GED_CtrlEv {
    uint8_t wel;
    ae2f_struct ae2f_cDsAllocOwn list;
} GED_CtrlEvt;

typedef bool(*GED_fpCtrlEvCond_t)(const void*);

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvKill(GED_CtrlEvt* mgr);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvResize(GED_CtrlEvt* mgr, size_t size);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvSort(GED_CtrlEvt* mgr, const ae2f_fpCmp_t fpcmp);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvGetRange(const GED_CtrlEvt* mgr, const GED_fpCtrlEvCond_t fpcond, size_t* Min, size_t* Max);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvElement(const GED_CtrlEvt* mgr, size_t i, void* lpEl);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvElement_Set(GED_CtrlEvt* mgr, size_t i, const void* lpEl);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_CtrlEvMake(GED_CtrlEvt* mgr, uint8_t elsize);

// No Element has met the condition.
#define GED_errCtrlEvGetRange_COND_MET_NONE ae2f_ds_Arr_NOT_FOUND

// Only an element has met the condition
#define GED_errCtrlEvGetRange_COND_MET_ONLY_ONE ae2f_errGlob_DONE_HOWEV

#endif