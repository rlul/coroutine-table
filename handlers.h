#pragma once
#include <Windows.h>

namespace UI::Handlers
{
	bool OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
	void OnDestroy(HWND hwnd);
	int OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
}
