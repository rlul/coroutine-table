#include "mainwindow.h"
#include "handlers.h"
#include <Windows.h>
#include <windowsx.h>

HWND UI::g_hWnd;
HWND UI::g_hTable;
HWND UI::g_hButtonNext;

LRESULT CALLBACK UI::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_CREATE, Handlers::OnCreate);
		HANDLE_MSG(hwnd, WM_DESTROY, Handlers::OnDestroy);
		HANDLE_MSG(hwnd, WM_CLOSE, Handlers::OnDestroy);
		HANDLE_MSG(hwnd, WM_COMMAND, Handlers::OnCommand);

		default: return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void UI::Setup(HINSTANCE instance)
{
	if (!instance)
	{
		MessageBox(NULL, "Failed to get instance", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (g_hWnd)
	{
		MessageBox(NULL, "UI already set up", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = instance;
	wc.lpszClassName = "MainWindow";
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	g_hWnd = CreateWindowEx(0, "MainWindow", "coroutine-tables", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
			WINDOW_WIDTH, WINDOW_HEIGHT, HWND_DESKTOP, NULL, instance, NULL);

	ShowWindow(g_hWnd, SW_SHOW);
}
