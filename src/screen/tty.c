#include <system/memory.h>
#include <dynamic_libs/os_functions.h>
#include <sys/iosupport.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "font.h"
#include "tty.h"

/* Definitions */
#define BUF_ADDR_0 (u32*)0xF4000000
#define BUF_ADDR_1 (u32*)0xF4708000
#define BUF_SIZE_0 0x00708000
#define BUF_SIZE_1 0x00348000
#define BUFFER_SIDE_OFFSET 0x69000
#define CHAR_SIZE_X (8)
#define CHAR_SIZE_Y (8)

#define COL_MAX 105
#define LINE_MAX 59

/* Globals */
u32* framebuffer = BUF_ADDR_1;
u32  framebuffer_size = BUF_SIZE_1;

u32 line = 0;
u32 column = 0;

/* Initialization and deinitialization */
static ssize_t tty_write(struct _reent *r, int fd, const char *ptr, size_t len);

static devoptab_t dotab_stdout;

void tty_init()
{
    OSScreenInit();
    OSScreenSetBufferEx(1, framebuffer);
    OSScreenEnableEx(1, 1);
	
    tty_clear(0);
	
	memset((u8*)&dotab_stdout, 0, sizeof(devoptab_t));
	dotab_stdout.name = "stdout_tty";
	dotab_stdout.write_r = &tty_write;
	
	devoptab_list[STD_OUT] = &dotab_stdout;
	devoptab_list[STD_ERR] = &dotab_stdout;
}

void tty_end()
{
	tty_clear(0);
}

/* Screen functions */
void tty_clear(u32 color)
{
	OSScreenClearBufferEx(1, color);
	tty_flip();
	OSScreenClearBufferEx(1, color);
	tty_flip();
	
	line = 0;
	column = 0;
}

void tty_flip()
{
	DCFlushRange(framebuffer, framebuffer_size);
    OSScreenFlipBuffersEx(1);
}

/* Char drawing (that comes from iosuhax) */
void tty_draw_char(char c, u32 x, u32 y)
{
	if(c < 32)
		return;
	c -= 32;
	
	u8* charData = (u8*)&font_bin[(CHAR_SIZE_X * CHAR_SIZE_Y * c) / 8];
	
	u32 * fb = &framebuffer[x + y * 896];

	int i, j;
	for(i = 0; i < CHAR_SIZE_Y; i++)
	{
		u8 v= *(charData++);
		for(j = 0; j < CHAR_SIZE_X; j++)
		{
			if(v & 1)
			{
				fb[0] = 0xFFFFFFFF;
				fb[0x69000] = 0xFFFFFFFF;
			}
			else
			{
				fb[0] = 0x00000000;
				fb[0x69000] = 0x00000000;
			}
			v >>= 1;
			fb++;
		}
		fb += 896 - CHAR_SIZE_X;
	}
}

/* Print functions wrappers */
void tty_scroll()
{
	// Scroll the buffer of 8 pixels
	memcpy(&framebuffer[0x00000], &framebuffer[0x01C00], 0x19D000);
	memcpy(&framebuffer[0x69000], &framebuffer[0x6AC00], 0x19D000);
	
	// Clear the last 8 pixel lines
	memset(&framebuffer[0x67400], 0, 0x7000);
	memset(&framebuffer[0xD0400], 0, 0x7000);
	
	tty_flip();
}

void tty_print_char(char c)
{
	switch(c)
	{
		case '\n':
			column = 0;
			line++;
			if (line > LINE_MAX)
			{
				tty_scroll();
				line = LINE_MAX;
			}
			break;
		case '\b':	// Backspace
			if (column == 0)
			{
				line--;
				column = COL_MAX;
			}
			else
			{
				column--;
			}
			tty_draw_char(' ', column, line);
			break;
		case '\r':
			column = 0;
		case '\0':
			return;
		default:
			if (c >= 32 && c < 128)
			{
				if (column > COL_MAX)
				{
					line++;
					column = 0;
				}
				if (line > LINE_MAX)
				{
					tty_scroll();
					line = LINE_MAX;
					column = 0;
				}
				tty_draw_char(c, column * 8, line * 8);
				column++;
			}
			break;
	}
}

/* devoptabs */
static ssize_t tty_write(struct _reent *r, int fd, const char *ptr, size_t len)
{
	for (size_t i = 0; i < len; i++)
		tty_print_char(ptr[i]);
	tty_flip();
	return len;
}