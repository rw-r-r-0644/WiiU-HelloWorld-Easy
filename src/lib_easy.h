/*
 * lib_easy.h
 *
 * Provides an easy-to-use library for wii u
 * usefull for test and beginners
 *
 * All the "complex" Wii U stuff is here
 *
*/

#ifndef EASYFUNCTIONS_H
#define EASYFUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <malloc.h>
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/fs_functions.h"
#include "dynamic_libs/gx2_functions.h"
#include "dynamic_libs/sys_functions.h"
#include "dynamic_libs/vpad_functions.h"
#include "dynamic_libs/padscore_functions.h"
#include "dynamic_libs/socket_functions.h"
#include "dynamic_libs/ax_functions.h"
#include "fs/fs_utils.h"
#include "fs/sd_fat_devoptab.h"
#include "system/memory.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "common/common.h"

int vpadError = -1;
VPADData vpad;

int screen_buf0_size = 0;
int screen_buf1_size = 0;
unsigned char *screenBuffer;

void ucls() {
	OSScreenClearBufferEx(0, 0);
    OSScreenClearBufferEx(1, 0);
}

void ScreenInit() {
    //Init screen and screen buffers
    OSScreenInit();	
    screen_buf0_size = OSScreenGetBufferSizeEx(0);
    screen_buf1_size = OSScreenGetBufferSizeEx(1);
    screenBuffer = MEM1_alloc(screen_buf0_size + screen_buf1_size, 0x40);
    OSScreenSetBufferEx(0, screenBuffer);
    OSScreenSetBufferEx(1, (screenBuffer + screen_buf0_size));
    OSScreenEnableEx(0, 1);
    OSScreenEnableEx(1, 1);
    ucls(); //Clear screens
}

void flipBuffers() {
	// Flush the cache
    DCFlushRange(screenBuffer, screen_buf0_size);
    DCFlushRange((screenBuffer + screen_buf0_size), screen_buf1_size);
    // Flip buffers
    OSScreenFlipBuffersEx(0);
    OSScreenFlipBuffersEx(1);
}

int line;
void uprintf(const char* format, ...) {
	if(line==18) { //Out of gamepad screen
		ucls(); //Clear Screen
		line=0; //Reset line
	}
	char buff[255];
	va_list argptr;
	va_start(argptr, format);
	vsnprintf(buff, 255, format, argptr);
	va_end(argptr);
	for(int i=0; i<2; i++) {	//Print on both Buffers
		OSScreenPutFontEx(0, 0, line, buff);		//That is printed to TV
		OSScreenPutFontEx(1, 0, line, buff);		//That is printed on GamePad
		flipBuffers();
	}
	line++;
	
}
int isPressed(int button) {
	VPADRead(0, &vpad, 1, &vpadError);
	if(vpad.btns_h&button) return 1;
	else return 0;
}

void uInit() {
	//--Initialize function pointers--
    InitOSFunctionPointers();		//Coreinit functions.
    InitVPadFunctionPointers();		//For gamepad input
    memoryInitialize();				//You probably shouldn't care about this for now :P

    VPADInit();						//Init GamePad input library (needed for getting gamepad input)
	ScreenInit();					//Init OSScreen (all the complex stuff is in easyfunctions.h :P )
}
void uDeInit() {
	MEM1_free(screenBuffer);
	screenBuffer = NULL;
	memoryRelease();
}

#endif
