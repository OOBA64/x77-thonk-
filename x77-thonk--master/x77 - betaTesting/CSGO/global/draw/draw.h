#ifndef DRAW_H
#define DRAW_H
#ifdef _WIN32
#pragma once
#endif

namespace d
{
	extern void draw_outlined_rect(int x, int y, int w, int h, color col);
	extern void draw_line(int x, int y, int x1, int y1, color col);
	extern void draw_filled_rect(int x, int y, int w, int h, color col);
	extern void draw_string(int x, int y, color col, unsigned long font, const char* text, ...);
	extern void draw_string_centered(int x, int y, color col, unsigned long font, const char* text, ...);
	extern void draw_circle(int x, int y, int r, int s, color col);
	extern void draw_corner_box(int x, int y, int w, int h, const color col);
	extern void draw_gradient_rect(int x0, int y0, int x1, int y1, color top, color bot);
	extern void draw_string_box(unsigned long font, const char* str, int x, int y, color col, color top_col);
}

#endif // !DRAW_H