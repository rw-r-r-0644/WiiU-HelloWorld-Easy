#include "lib_easy.h"

int Menu_Main(void) {
	uprintf("Hello World!");
	while(1) { 
		//<---put stuff that should run continuously before exiting here--->
		
		updatePressedButtons(); //Update buttons state
		if(isPressed(VPAD_BUTTON_HOME)) break; //Check if home is pressed
	}
	uprintf("Exiting...");
	return 0;
}

