cmake_minimum_required(VERSION 3.5)

project(CDXRLearn)

#hw-00
add_executable(GetAdapters)

target_sources(GetAdapters
    PRIVATE
        hw-00/getAdapterInfo.cpp
)

target_link_libraries(GetAdapters
    PRIVATE
        dxgi
)

#hw-01
add_executable(HandleCommands)

target_sources(HandleCommands
    PRIVATE
        hw-01/handleCommands.cpp
)

target_link_libraries(HandleCommands
    PRIVATE
        dxgi
        D3D12
)

#hw-02
add_executable(PrepareRenderTarget
    hw-02/setRenderTarget.cpp
)

target_sources(PrepareRenderTarget
    PRIVATE
        hw-02/setRenderTarget.cpp
        hw-02/CDXRenderer.h
        hw-02/CDXRendererContext.h
)

target_link_libraries(PrepareRenderTarget
    PRIVATE
        dxgi
        D3D12
)
