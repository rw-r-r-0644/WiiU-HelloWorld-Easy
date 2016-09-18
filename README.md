# WiiU-HelloWorld-Easy  
The Easiest Wii U Homebrew Example™  
  
A very easy example for people that want to start with wii u homebrew  
  
## lib_easy functions  
### Init functions  
__uInit();__  
Init Screen and Gamepad Input  
### Screen functions  
__ucls();__  
Clear screen  
  
__uprintf(format, ...);__  
Same as printf()  
### Input functions  
__updatePressedButtons();__  
Updates buttons state  
  
__isPressed(int button);__  
Returns 1 if button is pressed an 0 if button isn't pressed
example: "if(isPressed(VPAD_BUTTON_HOME)) doSomething();"  
Other than VPAD_BUTTON_HOME, possible values are:  
VPAD_BUTTON_A, VPAD_BUTTON_B, VPAD_BUTTON_X, VPAD_BUTTON_Y, VPAD_BUTTON_LEFT, VPAD_BUTTON_RIGHT,  
VPAD_BUTTON_UP, VPAD_BUTTON_DOWN, VPAD_BUTTON_ZL, VPAD_BUTTON_ZR, VPAD_BUTTON_L, VPAD_BUTTON_R,  
VPAD_BUTTON_PLUS, VPAD_BUTTON_MINUS, VPAD_BUTTON_HOME, VPAD_BUTTON_SYNC, VPAD_BUTTON_STICK_R,  
VPAD_BUTTON_STICK_L, VPAD_BUTTON_TV  
### Deinit functions  
__uDeInit();__  
Deinit Screen and Gamepad Input  
