#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

#include <d3d12.h>
#pragma comment(lib, "D3d12")

#include <iostream>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class D3DRendererContext
{
public:
    bool setUp();

private:
    bool initDevice();
    bool initCommandManagers();

    ComPtr<ID3D12Device> device = nullptr;
    ComPtr<ID3D12CommandList> cmdList = nullptr;
    ComPtr<ID3D12CommandQueue> cmdQueue = nullptr;
    ComPtr<ID3D12CommandAllocator> cmdAlloc = nullptr;
};

bool D3DRendererContext::setUp()
{
    return initDevice() && initCommandManagers();
}

bool D3DRendererContext::initDevice()
{
    HRESULT hr = D3D12CreateDevice(
        nullptr,    //the first adapter that is enumerated by IDXGIFactory1::EnumAdapters
        D3D_FEATURE_LEVEL_12_0,
        __uuidof(ID3D12Device),
        (void**) &device
    );

    if (!SUCCEEDED(hr)) {
        std::cout << "Device creatation failed\n";
        return false;
    }

    std::cout << "Device created\n";
}

bool D3DRendererContext::initCommandManagers()
{
    //Allocator
    HRESULT hr = device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        __uuidof(ID3D12CommandAllocator),
        (void**)(&cmdAlloc)
    );
    
    if (!SUCCEEDED(hr)) {
        std::cout << "Allocator creatation failed\n";
        return false;
    }

    std::cout << "Allocator created\n";

    //List
    hr = device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        cmdAlloc.Get(),
        nullptr,
        __uuidof(ID3D12CommandList),
        (void**)(&cmdList)
    );

    if (!SUCCEEDED(hr)) {
        std::cout << "List creatation failed\n";
        return false;
    }

    std::cout << "List created\n";

    //Queue
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc;
    device->CreateCommandQueue(
        &cmdQueueDesc,
        __uuidof(ID3D12CommandQueue),
        (void**)(&cmdQueue)
    );

    if (!SUCCEEDED(hr)) {
        std::cout << "Queue creatation failed\n";
        return false;
    }

    std::cout << "Queue created\n";

    return true;
}

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
    D3DRendererContext ctx;
    ctx.setUp();

    return 0;
}
