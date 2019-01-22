#pragma once
#include "stdafx.h"
#include "MyDirectX.h"
#include <DXGI1_4.h>
#include <d3d12.h>
#include <wrl.h>
#include <windows.h>
#include <windowsx.h>
#include <DXGI1_4.h>
#include <d3d12.h>
#include <string>
using namespace std;
class MyDirectX
{

private:
	IDXGIFactory4 * mpDxgiFactory = nullptr;
	ID3D12Device * mpD3dDevice = nullptr;
	IDXGIAdapter1 * mpHardwareAdapter = nullptr;
public:
	MyDirectX();
	~MyDirectX();
	IDXGIFactory4 * getDxgiFactory(void);
	ID3D12Device * getD3Device(void);
	IDXGIAdapter1 * getHardwareAdapter(void);
	HRESULT Initialize(void);
	HRESULT InitializeFactoryDeviceAndHardware(void);
	HRESULT GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter);
};

