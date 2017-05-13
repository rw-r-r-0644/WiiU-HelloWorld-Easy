/* 
 *	vpad.h
 *	Function wrappers for VPAD
 */


#pragma once
#include "dynamic_libs/vpad_functions.h"

int vpad_error;
VPADData vpad_data;

#define update_buttons() VPADRead(0, &vpad_data, 1, &vpad_error)
#define button_pressed(button) ((vpad_data.btns_h & button) ? 1 : 0)