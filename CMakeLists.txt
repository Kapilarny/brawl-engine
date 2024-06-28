cmake_minimum_required(VERSION 3.28)
project(brawl_engine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glfw)

set(FT_DISABLE_ZLIB TRUE)
set(FT_DISABLE_BZIP2 TRUE)
set(FT_DISABLE_PNG TRUE)
set(FT_DISABLE_HARFBUZZ TRUE)
set(FT_DISABLE_OLD_INTERNALS TRUE)
set(FT_DISABLE_GZIP TRUE)
set(FT_DISABLE_LZW TRUE)
set(FT_DISABLE_BROTLI TRUE)

add_subdirectory(external/freetype)

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
        src/ecs/ecs.h
        src/ecs/entity_manager.cpp
        src/ecs/entity_manager.h
        src/ecs/component_array.cpp
        src/ecs/component_array.h
        src/ecs/component_manager.cpp
        src/ecs/component_manager.h
        src/ecs/isystem.cpp
        src/ecs/isystem.h
        src/ecs/system_manager.cpp
        src/ecs/system_manager.h
        src/ecs/ecs_manager.cpp
        src/ecs/ecs_manager.h
        src/ecs/components/transform.h
        src/ecs/components/texture_2d.h
        src/ecs/systems/draw_system.cpp
        src/ecs/systems/draw_system.h
        src/renderer/vertex_array.h
        src/renderer/buffers.h
        src/renderer/gl/gl_buffers.cpp
        src/renderer/gl/gl_buffers.h
        src/renderer/gl/gl_vertex_array.cpp
        src/renderer/gl/gl_vertex_array.h
        src/renderer/vertex_array.cpp
        src/memory/ptr_wrap.h
        src/renderer/renderer_2d.cpp
        src/renderer/renderer_2d.h
        src/renderer/shader.cpp
        src/renderer/shader.h
        src/renderer/texture.cpp
        src/renderer/texture.h
        src/renderer/buffers.cpp
        src/platform/input.h
        src/renderer/font_renderer.h
        src/renderer/font_renderer.cpp
        src/core/camera_2d.cpp
        src/core/camera_2d.h
)

target_link_libraries(brawl_engine PRIVATE -static glfw freetype)
target_include_directories(brawl_engine PRIVATE src external/glad/includes external/stb external/g-truc/ glm)
