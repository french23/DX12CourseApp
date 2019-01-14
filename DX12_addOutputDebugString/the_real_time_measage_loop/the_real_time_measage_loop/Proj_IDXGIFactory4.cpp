 // the_real_time_measage_loop.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
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
LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

HRESULT GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter)
{
	*ppAdapter = nullptr;
	SIZE_T vMemory = 0;
	HRESULT vResult = E_FAIL;
	
	for (UINT adapterIndex = 0; true; ++adapterIndex)
	{
		IDXGIAdapter1* pAdapterTEMP = nullptr;
		if (DXGI_ERROR_NOT_FOUND == pFactory->EnumAdapters1(adapterIndex, &pAdapterTEMP))
		{
			break;
		}
		if (SUCCEEDED(D3D12CreateDevice(pAdapterTEMP, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
		{
			//a struct to hold the adapter's information and call GetDesc1(..) to fill it with data.
			DXGI_ADAPTER_DESC1 vDXGI_ADAPTER_DESC1;
			pAdapterTEMP->GetDesc1(&vDXGI_ADAPTER_DESC1);
			wstring sStart = L"\n\nVideo Card Info and memory: ";
			wstring sAdapterDescription = vDXGI_ADAPTER_DESC1.Description;
			wstring sSpace = L" ";
			wstring sAdapterMemory = std::to_wstring(vDXGI_ADAPTER_DESC1.DedicatedVideoMemory);
			wstring sEnd = L"\n";
			wstring sCombined = sStart + sAdapterDescription + sSpace + sAdapterMemory + sEnd;
			OutputDebugString(sCombined.c_str());

			// Another video card may have passed the DX feature requirement, so check if this one has more memory.
			// If it does have more memory then call Release() on the smaller one we don't want anymore.
			if (vDXGI_ADAPTER_DESC1.DedicatedVideoMemory > vMemory)
			{
				// This "if" checks to see if we already chose an adapter and if so then release it because we have one with more memory.
				if ((*ppAdapter) != nullptr)
				{
					(*ppAdapter)->Release();
					*ppAdapter = nullptr;
				}

				// Update the video memory of our local variable vMemory so we can check against other cards.
				vMemory = vDXGI_ADAPTER_DESC1.DedicatedVideoMemory;

				// Set the adapter parameter, dereference it so we are updating the client's variable.
				*ppAdapter = pAdapterTEMP;
				vResult = S_OK;
			}
			else
			{
				// This card has the needed features, but does not have as much memory as another card we already found
				// so call Release() because we won't use it.
				pAdapterTEMP->Release();
			}
			// Output info on the video card
			// Create a struct to hold the adapter's information and call GetDesc1 to fill it with data.
		}

		else
		{
			pAdapterTEMP->Release();
		}
	}
	return vResult;
}
// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// calculate the size of the client area
	RECT wr = { 0, 0, 500, 400 };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

														  // create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",    // name of the window class
		L"Our First Windowed Program",    // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		300,    // x-position of the window
		300,    // y-position of the window
		wr.right - wr.left,    // width of the window
		wr.bottom - wr.top,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg = { 0 };
	

	//coustom line of code
		ComPtr<IDXGIFactory4> vpDxgiFactory;  // this is a pointer	
		ComPtr<ID3D12Device> vpD3dDevice;
		HRESULT vResult;
		//vResult = D3D12CreateDevice(nullptr,/* nullptr mean to create the default adapter*/	D3D_FEATURE_LEVEL_11_0,	IID_PPV_ARGS(&vpD3dDevice));
		vResult = CreateDXGIFactory1(IID_PPV_ARGS(&vpDxgiFactory));
		ComPtr<IDXGIAdapter1> hardwareAdapter;
		vResult = GetHardwareAdapter(vpDxgiFactory.Get(), &hardwareAdapter);
		
	//coustom line of code
		if (vResult == S_OK)
		{
			vResult = D3D12CreateDevice(
				hardwareAdapter.Get(),
				D3D_FEATURE_LEVEL_11_0,
				IID_PPV_ARGS(&vpD3dDevice)
			);

			if (vResult == S_OK)
			{
				// Let's see how much memory this video card GPU has...
				DXGI_ADAPTER_DESC1 vDXGI_ADAPTER_DESC1;
				hardwareAdapter.Get()->GetDesc1(&vDXGI_ADAPTER_DESC1);

				wstring vDedicatedVideoMemory = std::to_wstring(vDXGI_ADAPTER_DESC1.DedicatedVideoMemory);
				wstring vOutputMessage = L"Success - ID3D12Device was created and the video card memory is " + vDedicatedVideoMemory;
				MessageBox(nullptr, vOutputMessage.c_str(), L"Working!!", MB_OK);
			}
			else
			{
				MessageBox(nullptr, L"FAIL, adapter was created but ID3D12Device was not!", L"Working, but we have a problem!", MB_OK);
			}
		}
		else
		{
			MessageBox(nullptr, L"FAIL to create the adapter.", L"Working, but we have a problem!", MB_OK);
		}

	// Enter the infinite message loop
	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);

			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			// Run game code here
			// ...
			// ...
		}
	}
	//coustom if statments
		/*if (vpDxgiFactory != nullptr)
		{
			vpDxgiFactory->Release();
			vpDxgiFactory = nullptr;
		}
		
		if (vpDxgiFactory != nullptr)
		{
			vpDxgiFactory->Release();
		}


		if (vpD3dDevice != nullptr)
		{
			vpD3dDevice->Release();
		}*/

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
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
