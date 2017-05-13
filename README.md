# WiiU-HelloWorld-Easy  
The Easiest Wii U Homebrew Example™  
  
A very easy example for people that want to start with wii u homebrew  
  
### Screen functions  
__clrscr();__  
Clears screen (same as ncurses)  
  
...and all the standard output functions! (but not the standard input function)  
(printf, puts, putc, ... ; if you never used those, you can look here: http://www.google.com/search?q=c+output+functions)  
  
### Input functions  
__update_buttons();__  
Updates buttons state  
  
__button_pressed(int button)__  
Returns 1 if button is pressed, 0 if button isn't pressed  
example: "if(isPressed(VPAD_BUTTON_HOME)) doSomething();"  
Other than VPAD_BUTTON_HOME, possible values are:  
VPAD_BUTTON_A, VPAD_BUTTON_B, VPAD_BUTTON_X, VPAD_BUTTON_Y, VPAD_BUTTON_LEFT, VPAD_BUTTON_RIGHT,  
VPAD_BUTTON_UP, VPAD_BUTTON_DOWN, VPAD_BUTTON_ZL, VPAD_BUTTON_ZR, VPAD_BUTTON_L, VPAD_BUTTON_R,  
VPAD_BUTTON_PLUS, VPAD_BUTTON_MINUS, VPAD_BUTTON_HOME, VPAD_BUTTON_SYNC, VPAD_BUTTON_STICK_R,  
VPAD_BUTTON_STICK_L, VPAD_BUTTON_TV  
  
### FS functions  
The standard C filesystem functions  
(open(), read(), fopen(), fwrite(), ... ; if you never used those, you can look here: http://www.google.com/search?q=c+file+functions)  
  
### Wii U functions  
You can access all the Wii U functions from all the Wii U libraries  
For a list and of them look here: http://wiiubrew.org/wiki/Cafe_OS#Libraries  
  
#### Bugs  
Is seems like the used implementation of printf won't send the input to the screen until a "\n" (newline) character is sent  
  