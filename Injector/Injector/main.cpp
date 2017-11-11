/*	ToDo
 *	-Fix open file dialogue for dll's
 *	-Allow drag/drop for dll's
 *	
 *	-Allow sorting by ID/Process in process list
 *	
 *	-Fix up UI
 *		-Fix overlayed text
 *		-Fix sizing issues
 *		-Fix alignment
 *		-Fix font
 *		-General prettification
 *		
 *	-Implement more injection methods
 */

#include "main.h"

#define IC_LISTVIEW_DLL		101
#define IC_LISTVIEW_PROC	102
#define IC_LISTVIEW_ADD		103
#define IC_LISTVIEW_REM		104
#define IC_LISTVIEW_CLR		105
#define IC_LISTVIEW_PCK		106
#define IC_LISTVIEW_REF		107
#define IC_LBL_PROC			108
#define IC_LBL_PROCINFO		109
#define IC_BTN_INJECT		110

//Process instance
HINSTANCE hMainInst = NULL;

//Windows
HWND hMainWnd = NULL;
HWND hProcWnd = NULL;

//List views
HWND hDllList = NULL;
HWND hProcList = NULL;

//Labels
HWND hProcLbl = NULL;
HWND hProcInfoLbl = NULL;

//Buttons
HWND hSelectBtn = NULL;
HWND hInjectBtn = NULL;

//Menus
HMENU hContextMenu = NULL;

//Target process ID
DWORD targetID = 0;

void RefreshProcesses() 
{
	if (ListView_GetItemCount(hProcList) > 0)
		ListView_DeleteAllItems(hProcList);

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry)) 
	{
		do
		{
			char id[16] = { '\0' };
			sprintf_s(id, sizeof(id), "%lu", entry.th32ProcessID);

			LVITEM   lvi = { 0 };

			int item = ListView_GetItemCount(hProcList);

			lvi.iItem = item;
			ListView_InsertItem(hProcList, &lvi);
			ListView_SetItemText(hProcList, item, 0, id);
			ListView_SetItemText(hProcList, item, 1, entry.szExeFile);
		} while (Process32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			//List view
			LVCOLUMN lvc = { 0 };

			hDllList = CreateWindowEx(NULL, WC_LISTVIEW, "", WS_BORDER | WS_VISIBLE | WS_CHILD | WS_VSCROLL | LVS_SINGLESEL | LVS_REPORT, 1, 1, 380, 200, hwnd, (HMENU)IC_LISTVIEW_DLL, hMainInst, NULL);

			ListView_SetExtendedListViewStyle(hDllList, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;
			lvc.fmt = LVCFMT_LEFT;

			lvc.iSubItem = 0;
			lvc.cx = 120;
			lvc.pszText = "Name";
			ListView_InsertColumn(hDllList, 0, &lvc);

			lvc.iSubItem = 1;
			lvc.cx = 260;
			lvc.pszText = "Path";
			ListView_InsertColumn(hDllList, 1, &lvc);

			//Labels
			hProcLbl = CreateWindowEx(NULL, "STATIC", "Process: ", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_NOTIFY, 5, 210, 65, 25, hwnd, (HMENU)IC_LBL_PROC, hMainInst, NULL);
			hProcInfoLbl = CreateWindowEx(NULL, "STATIC", "--", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_NOTIFY, 65, 210, 250, 25, hwnd, (HMENU)IC_LBL_PROCINFO, hMainInst, NULL);

			//Buttons
			hInjectBtn = CreateWindowEx(NULL, "BUTTON", "Inject", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 330, 210, 45, 25, hwnd, (HMENU)IC_BTN_INJECT, hMainInst, NULL);
		}break;

		case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code)
			{
				case NM_RCLICK:
				{
					if ((((LPNMHDR)lParam)->hwndFrom) == hDllList)
					{
						POINT point;
						GetCursorPos(&point);

						hContextMenu = CreatePopupMenu();

						AppendMenu(hContextMenu, MF_STRING, IC_LISTVIEW_ADD, "Add");
						AppendMenu(hContextMenu, MF_STRING, IC_LISTVIEW_REM, "Remove");
						AppendMenu(hContextMenu, MF_SEPARATOR, 0, NULL);
						AppendMenu(hContextMenu, MF_STRING, IC_LISTVIEW_CLR, "Clear");

						TrackPopupMenu(hContextMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);
						DestroyMenu(hContextMenu);
					}
				}break;
			}break;
		}break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IC_LISTVIEW_ADD:
				{
					char path[MAX_PATH + 1] = { '\0' };

					OPENFILENAME ofn;

					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hwnd;
					ofn.lpstrFile = path;
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = "Dynamic Link Library (*.dll)\0*.dll\0All files (*.*)\0*.*\0";
					ofn.lpstrDefExt = "dll";
					ofn.lpstrTitle = "Select a DLL";
					ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NONETWORKBUTTON;
					ofn.FlagsEx = 0;

					if (!GetOpenFileName(&ofn))
					{
						MessageBox(hwnd, "Unable to add dll.", "Error", MB_OK);
						break;
					}

					char file[MAX_PATH + 1] = { '\0' };

					if (_splitpath_s(ofn.lpstrFile, NULL, NULL, NULL, NULL, file, (MAX_PATH + 1), NULL, NULL)) 
					{
						MessageBox(hwnd, "Unable to add dll.", "Error", MB_OK);
						break;
					}

					LVITEM   lvi = { 0 };

					int item = ListView_GetItemCount(hDllList);

					lvi.iItem = item;
					ListView_InsertItem(hDllList, &lvi);
					ListView_SetItemText(hDllList, item, 0, file);
					ListView_SetItemText(hDllList, item, 1, ofn.lpstrFile);
				}break;

				case IC_LISTVIEW_REM:
				{
					int index = ListView_GetNextItem(hDllList, -1, LVNI_SELECTED);
					if (index != -1)
						ListView_DeleteItem(hDllList, index);
				}break;

				case IC_LISTVIEW_CLR:
				{
					if (ListView_GetItemCount(hDllList) > 0)
						ListView_DeleteAllItems(hDllList);
				}break;

				case IC_LBL_PROC:
				case IC_LBL_PROCINFO:
				{
					ShowWindow(hProcWnd, SW_SHOW);
					RefreshProcesses();
				}break;

				case IC_BTN_INJECT: 
				{
					if (targetID <= 0) 
					{
						MessageBox(hwnd, "Invalid process.", "Error", MB_OK);
						break;
					}

					if (ListView_GetItemCount(hDllList) <= 0) 
					{
						MessageBox(hwnd, "No dll's selected.", "Error", MB_OK);
						break;
					}

					for (int i = 0; i < ListView_GetItemCount(hDllList); i++)
					{
						char dll [274] = { '\0' };
						ListView_GetItemText(hDllList, i, 0, dll, sizeof(dll));
						//StandardInject(dll, targetID);
						MessageBox(hwnd, dll, "DLL Path", MB_OK); //dbg
					}
				}break;
			}break;
		}break;

		case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LRESULT)GetStockObject(NULL_BRUSH);
		}break;

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}break;

		case WM_DESTROY: 
		{
			PostQuitMessage(0);
		}break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	return 0;
}

LRESULT CALLBACK WndProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			//List view
			LVCOLUMN lvc = { 0 };

			hProcList = CreateWindowEx(NULL, WC_LISTVIEW, "", WS_BORDER | WS_VISIBLE | WS_CHILD | WS_VSCROLL | LVS_SINGLESEL | LVS_REPORT, 1, 1, 267, 200, hwnd, (HMENU)IC_LISTVIEW_PROC, hMainInst, NULL);

			ListView_SetExtendedListViewStyle(hProcList, LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;
			lvc.fmt = LVCFMT_LEFT;

			lvc.iSubItem = 0;
			lvc.cx = 40;
			lvc.pszText = "ID";
			ListView_InsertColumn(hProcList, 0, &lvc);

			lvc.iSubItem = 1;
			lvc.cx = 210;
			lvc.pszText = "Name";
			ListView_InsertColumn(hProcList, 1, &lvc);

			//Add processes
			RefreshProcesses();
		}break;

		case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code)
			{
				case NM_RCLICK:
				{
					if ((((LPNMHDR)lParam)->hwndFrom) == hProcList)
					{
						POINT point;
						GetCursorPos(&point);

						hContextMenu = CreatePopupMenu();

						AppendMenu(hContextMenu, MF_STRING, IC_LISTVIEW_PCK, "Select");
						AppendMenu(hContextMenu, MF_SEPARATOR, 0, NULL);
						AppendMenu(hContextMenu, MF_STRING, IC_LISTVIEW_REF, "Refresh");

						TrackPopupMenu(hContextMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);
						DestroyMenu(hContextMenu);
					}break;
				}break;
			}break;
		}break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IC_LISTVIEW_PCK:
				{
					int index = ListView_GetNextItem(hProcList, -1, LVNI_SELECTED);
					if (index != -1)
					{
						char id[16] = { '\0' };
						char proc[274] = { '\0' };
						char procinfo[274] = { '\0' };

						ListView_GetItemText(hProcList, index, 0, id, sizeof(id));
						ListView_GetItemText(hProcList, index, 1, proc, sizeof(proc));

						sprintf_s(procinfo, sizeof(procinfo), "[%s] %s", id, proc);

						Static_SetText(hProcInfoLbl, procinfo);

						targetID = StrToIntA(id);

						ShowWindow(hProcWnd, SW_HIDE);
					}
					else
					{
						MessageBox(hwnd, "Invalid process selected.", "Error", MB_OK);
					}
				}break;

				case IC_LISTVIEW_REF:
				{
					RefreshProcesses();
				}break;
			}break;
		}break;

		case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LRESULT)GetStockObject(NULL_BRUSH);
		}break;

		case WM_CLOSE:
		{
			ShowWindow(hProcWnd, SW_HIDE);
		}break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	if (OleInitialize(NULL) != S_OK)
		return 1;

	InitCommonControls();

	INITCOMMONCONTROLSEX icc = { 0 };
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_LISTVIEW_CLASSES;
	if (!InitCommonControlsEx(&icc))
		return 1;

	WNDCLASSEX WC;
	WC.cbSize = sizeof(WNDCLASSEX);
	WC.style = CS_HREDRAW | CS_VREDRAW;
	WC.lpfnWndProc = WndProc;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = hInstance;
	WC.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	WC.hCursor = LoadCursor(NULL, IDC_ARROW);
	WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WC.lpszMenuName = NULL;
	WC.lpszClassName = "PaladinInjector";
	WC.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	WNDCLASSEX WC2;
	WC2.cbSize = sizeof(WNDCLASSEX);
	WC2.style = CS_HREDRAW | CS_VREDRAW;
	WC2.lpfnWndProc = WndProc2;
	WC2.cbClsExtra = 0;
	WC2.cbWndExtra = 0;
	WC2.hInstance = hInstance;
	WC2.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	WC2.hCursor = LoadCursor(NULL, IDC_ARROW);
	WC2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WC2.lpszMenuName = NULL;
	WC2.lpszClassName = "PaladinInjectorProcesses";
	WC2.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&WC))
		return 1;

	if (!RegisterClassEx(&WC2))
		return 1;

	hMainWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "PaladinInjector", "Paladin Injector", WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 50, 50, 402, 282, NULL, NULL, hInstance, NULL);

	if (!hMainWnd)
		return 1;

	hProcWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "PaladinInjectorProcesses", "Select a Process", WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 50, 50, 289, 244, NULL, NULL, hInstance, NULL);

	if (!hProcWnd)
		return 1;

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}