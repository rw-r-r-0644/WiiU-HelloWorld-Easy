/*
 *	screen.h
 *	Function wrappers for Screen
 */
 
#pragma once
#include <screen/tty.h>

#define clrscr() tty_clear(0)
