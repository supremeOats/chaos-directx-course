#pragma once

#include <dxgi1_6.h>
#pragma comment(lib, "dxgi.lib")

#include <d3d12.h>
#pragma comment(lib, "D3d12")

#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

struct D3DRendererContext
{
    //GPUs & Device
    ComPtr<IDXGIFactory> pFactory = nullptr;
    ComPtr<IDXGIAdapter> pAdapter = nullptr;
    ComPtr<ID3D12Device> device = nullptr;
    
    //Commands
    ComPtr<ID3D12GraphicsCommandList> cmdList = nullptr;
    ComPtr<ID3D12CommandQueue> cmdQueue = nullptr;
    ComPtr<ID3D12CommandAllocator> cmdAlloc = nullptr;

    //Resource/Target
    ComPtr<ID3D12DescriptorHeap> rtvHeap = nullptr;    
    ComPtr<ID3D12Resource> target = nullptr;
};
