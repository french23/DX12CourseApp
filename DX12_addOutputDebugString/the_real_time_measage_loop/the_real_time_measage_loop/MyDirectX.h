#pragma once
#include "stdafx.h"
#include <DXGI1_4.h>
#include <d3d12.h>
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
};

