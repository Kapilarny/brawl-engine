cmake_minimum_required(VERSION 3.28)
project(brawl_engine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)

add_executable(brawl_engine
        external/glad/src/gl.c
        src/main.cpp
        src/platform/platform.h
        src/defines.h
        src/platform/win32/platform_win32.cpp
        src/core/logger.h
        src/core/logger.cpp
        src/memory/bmemory.cpp
        src/memory/bmemory.h
        src/renderer/renderer_frontend.h
        src/core/frame_data.h
        src/core/bclock.cpp
        src/core/bclock.h
        src/renderer/gl/gl_backend.cpp
        src/renderer/gl/gl_backend.h
        src/renderer/renderer_frontend.cpp
        src/renderer/gl/gl_shader.cpp
        src/renderer/gl/gl_shader.h
        src/memory/bvector.cpp
        src/memory/bvector.h
        src/memory/bstring.cpp
        src/memory/bstring.h
        src/renderer/gl/gl_texture.cpp
        src/renderer/gl/gl_texture.h
        src/core/camera.cpp
        src/core/camera.h
)

target_link_libraries(brawl_engine PRIVATE glfw)
target_include_directories(brawl_engine PRIVATE src external/glad/includes external/stb external/g-truc/)