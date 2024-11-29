#include <GED/Ctrl/MousePoint.h>

ae2f_SHAREDEXPORT ae2f_float_t
GED_CtrlMousePointX = 0,
GED_CtrlMousePointY = 0;

// Not neccesary to reveal
ae2f_SHAREDEXPORT ae2f_float_t* GED_CtrlMousePointptrX() {
	return &GED_CtrlMousePointX;
}

// Not neccesary to reveal
ae2f_SHAREDEXPORT ae2f_float_t* GED_CtrlMousePointptrY() {
	return &GED_CtrlMousePointY;
}