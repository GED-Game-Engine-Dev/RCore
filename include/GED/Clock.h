#if !defined(GED_Clock_h)
#define GED_Clock_h
#include <ae2f/Cast.h>
#include <ae2f/Call.h>
#include <time.h>

ae2f_extern ae2f_SHAREDCALL time_t GED_Clock_Now(time_t NewCastDuration ae2f_WhenCXX(=0));
#endif // !defined(GED_Clock_h)