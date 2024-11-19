#include <GED/Ctrl/MousePoint.h>

ae2f_SHAREDEXPORT ae2f_float_t
GED_Ctrl_MousePoint_X = 0,
GED_Ctrl_MousePoint_Y = 0;

// Not neccesary to reveal
ae2f_SHAREDEXPORT ae2f_float_t* GED_Ctrl_MousePoint_ptrX() {
	return &GED_Ctrl_MousePoint_X;
}

// Not neccesary to reveal
ae2f_SHAREDEXPORT ae2f_float_t* GED_Ctrl_MousePoint_ptrY() {
	return &GED_Ctrl_MousePoint_Y;
}