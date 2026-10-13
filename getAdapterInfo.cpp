#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

#include <iostream>

void print_luid(const LUID luid)
{
    std::cout << "Low Part: " << luid.LowPart << '\n';
    std::cout << "High Part: " << luid.HighPart << '\n';
}

void print_adapter_desc(const DXGI_ADAPTER_DESC desc)
{
    std::cout << "Description: "; std::wcout << desc.Description << '\n';
    std::cout << "Vendor ID: " << desc.VendorId << '\n';
    std::cout << "Device ID: " << desc.DeviceId << '\n';
    std::cout << "Subsystem ID: " << desc.SubSysId << '\n';
    std::cout << "Revision: " << desc.Revision << '\n';
    std::cout << "Dedicated Video Memory: " << desc.DedicatedVideoMemory << '\n';
    std::cout << "Dedicated System Memory: " << desc.DedicatedSystemMemory << '\n';
    std::cout << "Shared System Memory: " << desc.SharedSystemMemory << '\n';
    print_luid(desc.AdapterLuid);
}

int main()
{
    IDXGIFactory* pFactory = nullptr;
    HRESULT hrFactory = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory));

    if (!SUCCEEDED(hrFactory)) {
        std::cout << "Factory creation failed\n";
        pFactory->Release();

        return 0;
    }

    std::cout << "Factory created\n";

    IDXGIAdapter* pAdapter;
    for (UINT adapterIndex = 0; pFactory->EnumAdapters(adapterIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND; ++adapterIndex)
    {
        DXGI_ADAPTER_DESC adapterDesc;
        HRESULT hrAdapter = pAdapter->GetDesc(&adapterDesc);
        
        if (!SUCCEEDED(hrAdapter)) {
            std::cout << "Adapter " << adapterIndex << " creation failed\n";
            pAdapter->Release();
            break;
        }
        
        print_adapter_desc(adapterDesc); std::cout << '\n';

        pAdapter->Release();
    }

    pFactory->Release();

    return 0;
}
