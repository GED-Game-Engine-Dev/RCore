#if !defined(GED_Ctrl_Event_h)
#define GED_Ctrl_Event_h
#include <ae2f/Ds/Arr.h>
#include <ae2f/Cast.h>
#include <ae2f/Call.h>
#include <stdint.h>

// inside is Allocator::cOwner. (aka ae2f_ds_Alloc_Owner)
typedef struct GED_Ctrl_Ev {
    uint8_t wel;
    ae2f_struct ae2f_cDsAllocOwn list;
} GED_Ctrl_Ev_t;

typedef bool(*GED_Ctrl_Ev_fpCond_t)(const void*);

ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_Kill(GED_Ctrl_Ev_t* mgr);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_Resize(GED_Ctrl_Ev_t* mgr, size_t size);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_Sort(GED_Ctrl_Ev_t* mgr, const ae2f_fpCmp_t fpcmp);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_GetRange(const GED_Ctrl_Ev_t* mgr, const GED_Ctrl_Ev_fpCond_t fpcond, size_t* Min, size_t* Max);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_Element(const GED_Ctrl_Ev_t* mgr, size_t i, void* lpEl);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_Element_Set(GED_Ctrl_Ev_t* mgr, size_t i, const void* lpEl);
ae2f_extern ae2f_SHAREDCALL ae2f_err_t GED_Ctrl_Ev_Make(GED_Ctrl_Ev_t* mgr, uint8_t elsize);

// No Element has met the condition.
#define GED_Ctrl_Ev_GetRange_COND_MET_NONE ae2f_ds_Arr_NOT_FOUND

// Only an element has met the condition
#define GED_Ctrl_Ev_GetRange_COND_MET_ONLY_ONE ae2f_errGlob_DONE_HOWEV

#endif // GED_Ctrl_Custom_h