#pragma once
#include <d3d9.h>
#include "../Framework.hpp"

// For Nuklear
#include "../main.hpp"
#include "nuklear_d3d9.h"

#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

#ifdef __APPLE__
#define NK_SHADER_VERSION "#version 150\n"
#else
#define NK_SHADER_VERSION "#version 300 es\n"
#endif


namespace Paladin
{
	class CDrawing;
	extern CDrawing draw;

	class CDrawing
	{ };

	CDrawing draw;
}

struct media {
	GLint skin;
	struct nk_image menu;
	struct nk_image check;
	struct nk_image check_cursor;
	struct nk_image option;
	struct nk_image option_cursor;
	struct nk_image header;
	struct nk_image window;
	struct nk_image scrollbar_inc_button;
	struct nk_image scrollbar_inc_button_hover;
	struct nk_image scrollbar_dec_button;
	struct nk_image scrollbar_dec_button_hover;
	struct nk_image button;
	struct nk_image button_hover;
	struct nk_image button_active;
	struct nk_image tab_minimize;
	struct nk_image tab_maximize;
	struct nk_image slider;
	struct nk_image slider_hover;
	struct nk_image slider_active;
};


IDirect3DDevice9Ex					*pDeviceEx{};
IDirect3DDevice9					*pDevice{};
IDirect3D9Ex						*pObjectEx{};
D3DPRESENT_PARAMETERS				dxParameters{};
D3DDEVICE_CREATION_PARAMETERS		cpCreationParameters{};

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (nk_d3d9_handle_event(hWnd, msg, wParam, lParam))
		return 0;

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

void CDirectXDrawing::ChangeWindowClickability(bool bClickable)
{
	unsigned uStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	uStyle &= ~WS_EX_LAYERED;
	uStyle |= bClickable ? WS_EX_LAYERED : ~WS_EX_LAYERED;
	SetWindowLong(hWnd, GWL_EXSTYLE, uStyle);
}

void CDirectXDrawing::CreateRenderTarget()
{
	RegisterClassEx(&wndWindow);
	hWnd = CreateWindowEx(WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED, L"Paladin Extensions Loader", L"Paladin Extensions Loader", WS_POPUP,
		iScreenSize[0] / 2 - iWindowSize[0] / 2, iScreenSize[1] / 2 - iWindowSize[1] / 2, iWindowSize[0], iWindowSize[1],
		nullptr, nullptr, wndWindow.hInstance, nullptr);
	SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA);
	SetLayeredWindowAttributes(hWnd, 0, 0, LWA_COLORKEY);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

void CDirectXDrawing::MakeWindowClickable()
{
	unsigned style = GetWindowLong(hWnd, GWL_EXSTYLE);
	if (style & ~WS_EX_LAYERED)
	{
		style &= WS_EX_LAYERED;
	}
	SetWindowLong(hWnd, GWL_EXSTYLE, style);
}

void CDirectXDrawing::MakeWindowUnclickable()
{
	unsigned style = GetWindowLong(hWnd, GWL_EXSTYLE);
	if (style & WS_EX_LAYERED)
	{
		style |= WS_EX_LAYERED;
	}
	SetWindowLong(hWnd, GWL_EXSTYLE, style);
}

void CDirectXDrawing::InitializeDevice()
{
	Direct3DCreate9Ex(D3D_SDK_VERSION, &pObjectEx);

	dxParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	dxParameters.BackBufferWidth = iWindowSize[0];
	dxParameters.BackBufferHeight = iWindowSize[1];
	dxParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	dxParameters.BackBufferCount = 1;
	dxParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	dxParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	dxParameters.hDeviceWindow = hWnd;
	dxParameters.EnableAutoDepthStencil = true;
	dxParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	dxParameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	dxParameters.Windowed = true;

	pObjectEx->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dxParameters, nullptr, &pDeviceEx);
	pDevice = static_cast< IDirect3DDevice9 * >(pDeviceEx);
	pDevice->GetCreationParameters(&cpCreationParameters);

	struct nk_context *ctx = nk_d3d9_init(pDevice, iWindowSize[0], iWindowSize[1]);

	nk_font_atlas *atlas;
	struct nk_font_config config = nk_font_config(14);
	config.oversample_h = 1;
	config.oversample_v = 1;
	config.range = nk_font_default_glyph_ranges();
	nk_d3d9_font_stash_begin(&atlas);
	nk_font *robot = nk_font_atlas_add_from_file(atlas, "C:\\Windows\\Fonts\\Roboto-Regular.ttf", 20, &config);
	nk_font *tahoma = nk_font_atlas_add_from_file(atlas, R"(C:\Windows\Fonts\Tahoma.ttf)", 16, &config);
	nk_font *fa = nk_font_atlas_add_from_file(atlas, "C:\\Users\\Cole\\Documents\\GitHub\\Paladin\\Resources\\Fonts\\fontawesome-webfont.ttf", 16, &config);
	nk_d3d9_font_stash_end();

	bool bRunning{ true };
	bool bDrag{};
	
// Skinning
	struct nk_color table[NK_COLOR_COUNT];
	table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
	table[NK_COLOR_WINDOW] = nk_rgba(56, 60, 66, 215);
	table[NK_COLOR_HEADER] = nk_rgba(56, 60, 66, 215);
	table[NK_COLOR_BORDER] = nk_rgba(80, 84, 89, 255);
	table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
	table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(68, 103, 131, 255);
	table[NK_COLOR_TOGGLE] = nk_rgba(42, 44, 48, 255);
	table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(42, 44, 48, 255);
	table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SELECT] = nk_rgba(82, 82, 82, 255); // Updated 5/9/18
	table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SLIDER] = nk_rgba(42, 44, 48, 255);
	table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(53, 88, 116, 255);
	table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(58, 93, 121, 255);
	table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(40, 40, 40, 255);
	table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
	table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
	table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
	table[NK_COLOR_SCROLLBAR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(58, 93, 121, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(68, 103, 131, 255);
	table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
	nk_style_from_table(ctx, table);

	nk_style_button btn{};
// Done Skinning
	while (bRunning)
	{
		nk_style_set_font(ctx, &robot->handle);
		RECT recWindowPos{};
		GetWindowRect(hWnd, &recWindowPos);
		static POINT pntOldCursorPosRelative{};
		if (GetAsyncKeyState(0x01))
		{
			MakeWindowClickable();
			POINT pntCursorPos{};
			GetCursorPos(&pntCursorPos);
			POINT pntCursorPosRelative{ pntCursorPos.x - recWindowPos.left, pntCursorPos.y - recWindowPos.top };

			if ((pntCursorPosRelative.x > 0 && pntCursorPosRelative.x <= iWindowSize[0] && pntCursorPosRelative.y > 0 && pntCursorPosRelative.y <= iBarHeight) || bDrag)
			{
				bDrag = true;
				if (!pntOldCursorPosRelative.x || !pntOldCursorPosRelative.y) pntOldCursorPosRelative = pntCursorPosRelative;

				SetWindowPos(hWnd, nullptr, (recWindowPos.left - pntOldCursorPosRelative.x) + pntCursorPosRelative.x, (recWindowPos.top - pntOldCursorPosRelative.y) + pntCursorPosRelative.y, iWindowSize[0], iWindowSize[1], 0);
				UpdateWindow(hWnd);
			}
		}
		else
		{
			MakeWindowUnclickable();
			pntOldCursorPosRelative = { 0, 0 };
			bDrag = false;
		}

		MSG msg;
		nk_input_begin(ctx);
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bRunning = NULL;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		nk_input_end(ctx);


// Creating the Window
		if (nk_begin(ctx, "Paladin Extensions", nk_rect(0, 0, 410, 285), NK_WINDOW_TITLE| NK_WINDOW_BORDER | NK_WINDOW_BORDER | NK_WINDOW_CLOSABLE | NK_WINDOW_NO_SCROLLBAR)) // ADD WIDGETS
		{
			// Nuklear Drawing Goes Here
		}
