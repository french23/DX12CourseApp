#include "stdafx.h"
#include "myDirectX.h"


myDirectX::myDirectX()
{
}


myDirectX::~myDirectX()
{
}
IDXGIFactory4 * myDirectX::getDxgiFactory(void)
{
	return mpDxgiFactory;
}
ID3D12Device *  myDirectX::getD3dDevice(void)
{
	return mpD3dDevice;
}
IDXGIAdapter1 * myDirectX::getHardwareAdapter(void)
{
	return mpHardwareAdapter;	
}