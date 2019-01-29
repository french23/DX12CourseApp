// the_real_time_measage_loop.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "myDirectX.h"
// include the basic windows header file
#include <windows.h>
#include <windowsx.h>
#include <DXGI1_4.h>
#include <d3d12.h>
#include <wrl.h>
#include <string>
using namespace std;
using namespace Microsoft::WRL;
#pragma comment( lib, "D3D12.lib" )
//#include "d3d12.lib"
//coustom line of code
#pragma comment(lib, "dxgi.lib")
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

myDirectX gMyDirectX;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)

{
	HRESULT hr;
	hr = gMyDirectX.Initialize();

	return 0;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}
