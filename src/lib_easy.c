#include "lib_easy.h"

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

void uprintf(const char* format, ...) {
  if(curr_line==18) { //Out of gamepad screen
    ucls(); //Clear Screen
    curr_line=0; //Reset line
  }
  char buff[255];
  va_list argptr;
  va_start(argptr, format);
  vsnprintf(buff, 255, format, argptr);
  va_end(argptr);
  for(int i=0; i<2; i++) {	//Print on both Buffers
    OSScreenPutFontEx(0, 0, curr_line, buff);		//That is printed to TV
    OSScreenPutFontEx(1, 0, curr_line, buff);		//That is printed on GamePad
    flipBuffers();
  }
  curr_line++;
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
