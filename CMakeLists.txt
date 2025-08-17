cmake_minimum_required(VERSION 3.20)
project(poison3d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

# Options to toggle targets
option(BUILD_WIN_SDL "Build Windows SDL2 app" ON)
option(BUILD_N64 "Build N64 (delegates to libdragon make)" OFF)
option(BUILD_DC "Build Dreamcast (delegates to KOS make)" OFF)

# --- Engine core ---
add_library(engine_core
  src/engine/core/camera.c
  src/engine/core/engine.c
  src/engine/core/mouse.c
  src/engine/core/font.c
  src/engine/image-formats/image_format_tga.c
  src/engine/renderers/renderer_gl.c
  src/engine/renderers/renderer_common.c
)

target_include_directories(engine_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/core
  ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderers
)

# --- Windows (SDL2 + OpenGL 1.1-style) ---
if(BUILD_WIN_SDL)
  add_executable(sandbox
    src/apps/sandbox/main.c
    src/platforms/platform_win_sdl.c
  )

  target_include_directories(sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms
  )

  target_link_libraries(sandbox PRIVATE engine_core)

  # Use SDL2 via vcpkg manifest if available, else try system SDL2
  find_package(SDL2 QUIET)
  if(SDL2_FOUND AND TARGET SDL2::SDL2)
    target_link_libraries(sandbox PRIVATE SDL2::SDL2)
  else()
    target_compile_definitions(sandbox PRIVATE SDL_MAIN_HANDLED)
    target_link_libraries(sandbox PRIVATE SDL2)
  endif()

  find_package(OpenGL REQUIRED)

  # Link to both OpenGL and GLU
  target_link_libraries(sandbox PRIVATE OpenGL::GLU OpenGL::GL)

  # Link against the Windows OpenGL loader (provides gl 1.1)
  if(WIN32)
    target_link_libraries(sandbox PRIVATE opengl32)
  endif()

  if(MSVC)
    target_compile_options(sandbox PRIVATE /W4 /permissive-)
    target_compile_options(engine_core PRIVATE /W4 /permissive-)
  else()
    target_compile_options(sandbox PRIVATE -Wall -Wextra -Werror=return-type)
    target_compile_options(engine_core PRIVATE -Wall -Wextra -Werror=return-type)
  endif()
endif()

# --- Stubs to delegate to make-based ports later ---
if(BUILD_N64)
  add_custom_target(n64 ALL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/platforms/n64
    COMMAND make
    COMMENT "Building N64 target via libdragon make (stub)"
  )
endif()

if(BUILD_DC)
  add_custom_target(dreamcast ALL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/platforms/dreamcast
    COMMAND make
    COMMENT "Building Dreamcast target via KOS make (stub)"
  )
endif()
