#include "../../main.h"

namespace d
{

	void draw_outlined_rect(int x, int y, int w, int h, color col)
	{
		i::surface->draw_set_color(col);
		i::surface->draw_outlined_rect(x, y, x + w, y + h);
	}

	void draw_line(int x, int y, int x1, int y1, color col) {
		i::surface->draw_set_color(col);
		i::surface->draw_line(x, y, x1, y1);
	}

	void draw_filled_rect(int x, int y, int w, int h, color col)
	{
		i::surface->draw_set_color(col);
		i::surface->draw_filled_rect(x, y, x + w, y + h);
	}

	void draw_string(int x, int y, color col, unsigned long font, const char* text, ...)
	{

		if (text == NULL)
			return;

		va_list	va_alist;
		char	buffer[1024];
		wchar_t	string[1024];

		va_start(va_alist, text);
		_vsnprintf(buffer, sizeof(buffer), text, va_alist);
		va_end(va_alist);

		MultiByteToWideChar(CP_UTF8, 0, buffer, 256, string, 256);

		i::surface->draw_set_text_pos(x, y);
		i::surface->draw_set_text_font(font);
		i::surface->draw_set_text_color(col);
		i::surface->draw_print_text(string, wcslen(string));

	}

	void draw_string_centered(int x, int y, color col, unsigned long font, const char* text, ...) 
	{

		if (text == NULL)
			return;

		va_list	va_alist;
		char	buffer[1024];
		wchar_t	string[1024];
		int		w, h;

		va_start(va_alist, text);
		_vsnprintf(buffer, sizeof(buffer), text, va_alist);
		va_end(va_alist);

		MultiByteToWideChar(CP_UTF8, 0, buffer, 256, string, 256);

		i::surface->get_text_size(font, string, w, h);
		i::surface->draw_set_text_pos(x - w / 2, y - h / 2);
		i::surface->draw_set_text_font(font);
		i::surface->draw_set_text_color(col);
		i::surface->draw_print_text(string, wcslen(string));

	}

	void draw_circle(int x, int y, int r, int s, color col)
	{
		i::surface->draw_set_color(col);
		i::surface->draw_outlined_circle(x, y, r, s);
	}

	void corner(int x, int y, int w, int h, const bool right, const bool down, color col)
	{
		const auto corner_x = right ? x - w : x;
		const auto corner_y = down ? y - h : y;
		const auto corner_w = down && right ? w + 1 : w;

		draw_outlined_rect(corner_x, y, corner_w, 1, col);
		draw_outlined_rect(x, corner_y, 1, h, col);
	}

	void draw_corner_box(int x, int y, int w, int h, const color col)
	{
		corner(x, y, w / 5, w / 2, false, false, col);		// top left
		corner(x, y + h, w / 5, w / 2, false, true, col);	// bottom left

		corner((x + w) - 1, y, w / 5, w / 2, true, false, col);		// top right
		corner((x + w) - 1, y + h, w / 5, w / 2, true, true, col);	// bottom right
	}

	void draw_gradient_rect(int x0, int y0, int x1, int y1, color top, color bot)
	{
		i::surface->draw_set_color(top);
		i::surface->draw_filled_rect_fade(x0, y0, x1, y1, 255, 255, false);

		i::surface->draw_set_color(bot);
		i::surface->draw_filled_rect_fade(x0, y0, x1, y1, 0, 255, false);
	}

	void draw_string_box(unsigned long font, const char* str, int x, int y, color col, color top_col)
	{
		RECT text_size = i::surface->get_text_size_rect(font, str);

		d::draw_filled_rect(x, y, text_size.right + 6, 14, col);
		d::draw_filled_rect(x, (y - 1), text_size.right + 6, 1, top_col);
		d::draw_string(x + 3, (y - 1), top_col, font, str);
	}

}