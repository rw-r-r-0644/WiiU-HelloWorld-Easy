#pragma once

#include <stdarg.h>
#include <common/types.h>

void tty_init();
void tty_end();
void tty_clear(u32 color);
void tty_flip();
void tty_draw_char(char c, u32 x, u32 y);
void tty_scroll();
void tty_print_char(char c);

