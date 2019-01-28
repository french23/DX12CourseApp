#pragma once
#include "stdafx.h"
#include <DXGI1_4.h>
#include <d3d12.h>
class myDirectX
{
public:
	myDirectX();
	~myDirectX();
	IDXGIFactory4 * getDxgiFactory(void);
	ID3D12Device *  getD3dDevice(void);
	IDXGIAdapter1 * getHardwareAdapter(void);
private:
	IDXGIFactory4 * mpDxgiFactory = nullptr;
	ID3D12Device * mpD3dDevice = nullptr;
	IDXGIAdapter1 * mpHardwareAdapter = nullptr;
};

