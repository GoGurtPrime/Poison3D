cmake_minimum_required(VERSION 3.20)
project(ttf2bitmap C)

set(CMAKE_C_STANDARD 99)
add_executable(ttf2bitmap main.c stb_truetype.h)

# Windows: produce a nice console exe
if (MSVC)
  target_compile_options(ttf2bitmap PRIVATE /W4)
else()
  target_compile_options(ttf2bitmap PRIVATE -Wall -Wextra -O2)
endif()
