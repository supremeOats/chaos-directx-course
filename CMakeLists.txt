cmake_minimum_required(VERSION 3.5)

project(CDXRLearn)

add_executable(GetAdapters)
target_sources(GetAdapters
    PRIVATE
        getAdapterInfo.cpp
)


target_link_libraries(GetAdapters
    PRIVATE
        dxgi
)
