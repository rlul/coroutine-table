#pragma once
#include <Windows.h>

namespace UI
{
	constexpr int MAX_COLUMN_LENGTH = 64;
	constexpr int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 400;

	enum Column_t
	{
		NAME = 0,
		SURNAME,
		AGE,
		ADDRESS,
		PHONE_NUMBER,
		TOTAL
	};

	extern HWND g_hWnd;
	extern HWND g_hTable;
	extern HWND g_hButtonNext;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Setup(HINSTANCE instance);
}
