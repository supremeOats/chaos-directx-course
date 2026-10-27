#pragma once

#include "D3DRendererContext.h"
#include <cassert>

#include <iostream>

FLOAT white[] = {0.0, 0.0, 0.0, 1.0};

class CDXRenderer
{
public:
    CDXRenderer(D3DRendererContext& ctx) : ctx(ctx) {}

    void prepareForRendering();
    void clearTarget(const float color[4]);

private:
    void createCommandManagers();
    void createRTV();
    void createTexture();

private:
    D3DRendererContext ctx;
};

void CDXRenderer::prepareForRendering()
{
    HRESULT hr;
    //create factory - skip
    //create device - no factory created & no adapter given => default adapter used
    hr = D3D12CreateDevice(
        nullptr,
        D3D_FEATURE_LEVEL_12_0,
        IID_PPV_ARGS(&ctx.device)
    );

    assert(SUCCEEDED(hr));

    createCommandManagers();

    createRTV();

    createTexture();
    
    //clear RTV happens after this function
}

void CDXRenderer::createCommandManagers()
{
    //create command queue, allocator -> list

    //Allocator
    HRESULT hr = ctx.device->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&ctx.cmdAlloc)
    );
    
    assert(SUCCEEDED(hr));

    //List
    hr = ctx.device->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        ctx.cmdAlloc.Get(),
        nullptr,
        IID_PPV_ARGS(&ctx.cmdList)
    );

    assert(SUCCEEDED(hr));

    //Queue
    D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
    ctx.device->CreateCommandQueue(
        &cmdQueueDesc,
        IID_PPV_ARGS(&ctx.cmdQueue)
    );

    assert(SUCCEEDED(hr));
}

void CDXRenderer::createRTV()
{
    //create render target view (RTV) descriptor heap (DH) (and DH desc)

    D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
    descHeapDesc.NumDescriptors = 1;
    descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    
    HRESULT hr = ctx.device->CreateDescriptorHeap(
        &descHeapDesc,
        IID_PPV_ARGS(&ctx.rtvHeap)
    );

    assert(SUCCEEDED(hr));
}

void CDXRenderer::createTexture()
{
    //create committed resource
    D3D12_RESOURCE_DESC resourceDesc = {};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    resourceDesc.Width = 600;
    resourceDesc.Height = 400;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
    
    D3D12_CLEAR_VALUE clearVal;
    clearVal.Color[0] = 0.0; clearVal.Color[1] = 0.0; clearVal.Color[2] = 0.0; clearVal.Color[3] = 1.0;
    clearVal.Format = resourceDesc.Format;

    D3D12_HEAP_PROPERTIES heapProps;
    heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    HRESULT hr = ctx.device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_RENDER_TARGET,
        &clearVal,
        IID_PPV_ARGS(&ctx.target)
    );

    assert(hr);

    //& create RTV
    hr = ctx.device->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_COMMON,
        &clearVal,
        IID_PPV_ARGS(&ctx.target)
    );

    assert(hr);
}

void CDXRenderer::clearTarget(const float color[4])
{
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = ctx.rtvHeap->GetCPUDescriptorHandleForHeapStart();
 
    ctx.cmdList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
 
    ctx.cmdList->ClearRenderTargetView(
        rtvHandle,
        color,
        0,
        nullptr
    );
}
