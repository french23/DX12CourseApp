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
	HRESULT Initialize(void);
private:
	IDXGIFactory4 * mpDxgiFactory = nullptr;
	ID3D12Device * mpD3dDevice = nullptr;
	IDXGIAdapter1 * mpHardwareAdapter = nullptr;
	ID3D12CommandQueue * mpID3D12CommandQueue = nullptr;
	HRESULT GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter);
	HRESULT InitializeFactoryDeviceAndHardware(void);
	HRESULT InitializeCommandObjects(void);
};

