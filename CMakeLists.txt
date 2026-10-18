cmake_minimum_required(VERSION 3.5)

project(CDXRLearn)

#hw-01
add_executable(GetAdapters)
target_sources(GetAdapters
    PRIVATE
        getAdapterInfo.cpp
)

target_link_libraries(GetAdapters
    PRIVATE
        dxgi
)

#hw-02
add_executable(HandleCommands)
target_sources(HandleCommands
    PRIVATE
        handleCommands.cpp
)

target_link_libraries(HandleCommands
    PRIVATE
        dxgi
        D3D12
)
