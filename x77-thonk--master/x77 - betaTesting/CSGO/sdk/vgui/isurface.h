#ifndef ISURFACE_H
#define ISURFACE_H
#ifdef _WIN32
#pragma once
#endif

class isurface
{
public:

	void draw_set_color(color col)
	{
		using original_fn = void(__thiscall*)(PVOID, color);
		u::call_vfunc<original_fn>(this, 14)(this, col);
	}

	void draw_filled_rect(int x0, int y0, int x1, int y1)
	{
		using original_fn = void(__thiscall*)(PVOID, int, int, int, int);
		u::call_vfunc<original_fn>(this, 16)(this, x0, y0, x1, y1);
	}

	void draw_outlined_rect(int x0, int y0, int x1, int y1)
	{
		using original_fn = void(__thiscall*)(PVOID, int, int, int, int);
		u::call_vfunc<original_fn>(this, 18)(this, x0, y0, x1, y1);
	}

	void draw_line(int x0, int y0, int x1, int y1)
	{
		using original_fn = void(__thiscall*)(PVOID, int, int, int, int);
		u::call_vfunc<original_fn>(this, 19)(this, x0, y0, x1, y1);
	}

	void draw_set_text_font(unsigned long font)
	{
		using original_fn = void(__thiscall*)(PVOID, unsigned long);
		u::call_vfunc<original_fn>(this, 23)(this, font);
	}

	void draw_set_text_color(color col)
	{
		using original_fn = void(__thiscall*)(PVOID, color);
		u::call_vfunc<original_fn>(this, 24)(this, col);
	}

	void draw_set_text_pos(int x, int y)
	{
		using original_fn = void(__thiscall*)(PVOID, int, int);
		u::call_vfunc<original_fn>(this, 26)(this, x, y);
	}

	void draw_print_text(const wchar_t* text, int text_length)
	{
		using original_fn = void(__thiscall*)(PVOID, const wchar_t*, int, int);
		u::call_vfunc<original_fn>(this, 28)(this, text, text_length, 0);
	}

	unsigned long create_font()
	{
		using original_fn = unsigned long(__thiscall*)(PVOID);
		return u::call_vfunc<original_fn>(this, 71)(this);
	}

	void set_font_glyph_set(unsigned long& font, const char* windows_font_name, int tall, int weight, int blur, int scanlines, int flags)
	{
		using original_fn = void(__thiscall*)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		u::call_vfunc<original_fn>(this, 72)(this, font, windows_font_name, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void get_text_size(unsigned long font, const wchar_t* text, int& width, int& tall)
	{
		using original_fn = void(__thiscall*)(PVOID, unsigned long, const wchar_t*, int&, int&);
		u::call_vfunc<original_fn>(this, 79)(this, font, text, width, tall);
	}

	void draw_outlined_circle(int x, int y, int radius, int segments)
	{
		using original_fn = void(__thiscall*)(PVOID, int, int, int, int);
		u::call_vfunc<original_fn>(this, 103)(this, x, y, radius, segments);
	}

	void draw_filled_rect_fade(int x0, int y0, int x1, int y1, size_t alpha0, size_t alpha1, bool horizontal)
	{
		using original_fn = void(__thiscall*)(PVOID, int, int, int, int, size_t, size_t, bool);
		u::call_vfunc<original_fn>(this, 123)(this, x0, y0, x1, y1, alpha0, alpha1, horizontal);
	}

	RECT get_text_size_rect(unsigned long font, const char* text)
	{
		const size_t	newsize			= 100;
		size_t			origsize		= strlen(text) + 1;
		size_t			convertedChars	= 0;
		wchar_t			wcstring[newsize];

		mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

		RECT rect; int x, y;
		get_text_size(font, wcstring, x, y);
		rect.left = x; rect.bottom = y;
		rect.right = x;
		return rect;
	}

};

#endif // !ISURFACE_H