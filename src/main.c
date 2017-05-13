#include <easy/easy.h>
#include <stdio.h>

int Menu_Main(void)
{
	// Display the "Hello World" message
	printf("Hello World!\n");
	
	// Wait for the user to press the Home Button
	while(1)
	{
		/* put stuff that should run continuously before exiting here */
		
		update_buttons();						// Update buttons state
		if (button_pressed(VPAD_BUTTON_HOME))	// Check if home is pressed
			break;								// Exit the while loop
	}
	
	// Display the exit message
	printf("Exiting...\n");
	
	// Return
	return 0;
}

