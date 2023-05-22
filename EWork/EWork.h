#pragma once

#include "resource.h"
#include "stdafx.h"

#define MAX_LOADSTRING 100

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Application {
	HWND hWnd;
	WNDCLASSEXW wcex;

	int hWnd_w = 1280, hWnd_h = 800;
public:
	LPDIRECT3D9              g_pD3D = nullptr;
	LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
	D3DPRESENT_PARAMETERS    g_d3dpp = {};

	void GetDesktopResolution(int& horizontal, int& vertical);
	bool InitWindow(HINSTANCE hInstance, int nCmdShow);
	bool InitDirect3D9();
	void CleanupDirect3D9();
	void InitImGui();
	void MainLoop();
	void ResetDevice();
	void CleanupImGui();
	void CleanupWindow();
};

extern Application gApplication;