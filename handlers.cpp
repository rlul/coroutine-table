#include "handlers.h"
#include "resource.h"
#include "mainwindow.h"
#include "person.h"
#include "generators.h"
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <string>

bool UI::Handlers::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	g_hTable = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS, 20, 20,
		740, 280, hwnd, (HMENU)IDI_TABLE, lpCreateStruct->hInstance, NULL);

	if (!g_hTable)
	{
		MessageBox(hwnd, "Failed to create table", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	LVCOLUMN lvc = {};
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;

	lvc.cx = 150;
	lvc.pszText = (LPSTR)"Name";
	ListView_InsertColumn(g_hTable, NAME, &lvc);
	lvc.cx = 200;
	lvc.pszText = (LPSTR)"Surname";
	ListView_InsertColumn(g_hTable, SURNAME, &lvc);
	lvc.pszText = (LPSTR)"Age";
	lvc.cx = 50;
	ListView_InsertColumn(g_hTable, AGE, &lvc);
	lvc.cx = 200;
	lvc.pszText = (LPSTR)"Address";
	ListView_InsertColumn(g_hTable, ADDRESS, &lvc);
	lvc.cx = 200;
	lvc.pszText = (LPSTR)"Phone Number";
	ListView_InsertColumn(g_hTable, PHONE_NUMBER, &lvc);

	g_hButtonNext = CreateWindowEx(0, "BUTTON", "Next", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 670, 310, 90, 30, hwnd,
		(HMENU)IDI_BUTTON_NEXT, lpCreateStruct->hInstance, NULL);

	if (!g_hButtonNext)
	{
		MessageBox(hwnd, "Failed to create button", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void UI::Handlers::OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

int UI::Handlers::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
		case IDI_BUTTON_NEXT:
		{
			static int i = 0;

			ListView_DeleteAllItems(g_hTable);
			
			for (const auto& person : Generate<Person_t>(10))
			{
				LVITEM lvi = {};
				char buffer[MAX_COLUMN_LENGTH];

				strcpy_s(buffer, MAX_COLUMN_LENGTH, person.name.c_str());

				lvi.mask = LVIF_TEXT;
				lvi.iItem = i;
				lvi.iSubItem = NAME;
				lvi.pszText = buffer;
				ListView_InsertItem(g_hTable, &lvi);

				strcpy_s(buffer, MAX_COLUMN_LENGTH, person.surname.c_str());
				ListView_SetItemText(g_hTable, i, SURNAME, buffer);
				strcpy_s(buffer, MAX_COLUMN_LENGTH, std::to_string(person.age).c_str());
				ListView_SetItemText(g_hTable, i, AGE, buffer);
				strcpy_s(buffer, MAX_COLUMN_LENGTH, person.address.c_str());
				ListView_SetItemText(g_hTable, i, ADDRESS, buffer);
				strcpy_s(buffer, MAX_COLUMN_LENGTH, person.phone_number.c_str());
				ListView_SetItemText(g_hTable, i, PHONE_NUMBER, buffer);

				++i;
			}
			i = 0;
			break;
		}

		default: break;
	}

	return 0;
}
