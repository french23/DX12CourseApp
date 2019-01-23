#include "stdafx.h"
#include "MyDirectX.h"


MyDirectX::MyDirectX()
{
}


MyDirectX::~MyDirectX()
{
	if (mpDxgiFactory != nullptr)
	{
		mpDxgiFactory->Release();
	}

	if (mpHardwareAdapter != nullptr)
	{
		mpHardwareAdapter->Release();
	}

	if (mpD3dDevice != nullptr)
	{
		mpD3dDevice->Release();
	}
}
IDXGIFactory4 * MyDirectX::getDxgiFactory(void)
{
	return 0;
}
ID3D12Device * MyDirectX::getD3Device(void)
{
	return 0;

}
IDXGIAdapter1 * MyDirectX::getHardwareAdapter(void)
{
	return 0;
}
HRESULT MyDirectX::Initialize(void)
{
	HRESULT hr;
	hr = InitializeFactoryDeviceAndHardware();

	return hr;
}
HRESULT MyDirectX::InitializeFactoryDeviceAndHardware()
{
	HRESULT hr = NULL;
	IDXGIFactory4 *  mpDxgiFactory;
	ID3D12Device  *  mpD3dDevice;
	IDXGIAdapter1 *  mpHardwareAdapter;
	return hr;
}
HRESULT MyDirectX::GetHardwareAdapter(IDXGIFactory4* pFactory, IDXGIAdapter1** ppAdapter)
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
