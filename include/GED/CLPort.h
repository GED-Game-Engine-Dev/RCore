#ifndef GED_CL_h
#define GED_CL_h

#include <ae2f/Cast.h>
#include <ae2f/Call.h>
#include <ae2f/errGlob.h>
#include <CL/cl.h>

ae2f_extern ae2f_SHAREDCALL cl_context GED_CLCtx;
ae2f_extern ae2f_SHAREDCALL cl_command_queue GED_CLQueue;
ae2f_extern ae2f_SHAREDCALL cl_platform_id GED_CLPlatform;
ae2f_extern ae2f_SHAREDCALL cl_device_id GED_CLDevice;

ae2f_extern ae2f_SHAREDCALL ae2f_err_t
GED_CLMk();

ae2f_extern ae2f_SHAREDCALL void
GED_CLDel();

#include <ae2fCL/Bmp/Bmp.h>
#define GED_BmpCLSrcDel ae2fCL_cBmpBuffDel

#endif