#pragma once
#include "stdafx.h"
#include <DXGI1_4.h>
#include <d3d12.h>
#include <wrl.h>
#include <string>
using namespace std;
class myDirectX
{
public:
	myDirectX();
	~myDirectX();
	IDXGIFactory4 * getDxgiFactory(void);
	ID3D12Device *  getD3dDevice(void);
	IDXGIAdapter1 * getDXGIAdapter1(void);
	HRESULT Initialize(HWND vhMainWnd);
	int getRenderTargetWidth(void);
	int getRenderTargetHeight(void);
private:
	int mRenderTargetWidth = 800;
	int mRenderTargetHeight = 600;
	IDXGIFactory4 * mpDxgiFactory = nullptr;
	ID3D12Device * mpD3dDevice = nullptr;
	IDXGIAdapter1 * mpHardwareAdapter = nullptr;
	ID3D12CommandQueue * mpID3D12CommandQueue = nullptr;
	ID3D12CommandAllocator * mpID3D12CommandAllocator = nullptr;
	ID3D12GraphicsCommandList * mpID3D12GraphicsCommandList = nullptr;
	IDXGISwapChain * mpIDXGISwapChain = nullptr;
	UINT m4xMsaaQuality = 0;
	HWND mhMainWnd = nullptr;
	HRESULT GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter);
	HRESULT InitializeFactoryDeviceAndHardware(void);
	HRESULT InitializeCommandObjects(void);
	HRESULT InitializeSwapChain(void);
};

