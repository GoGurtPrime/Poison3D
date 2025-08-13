# YourGame Starter (Windows + SDL2 + OpenGL 1.1-style)

This is a minimal, **C-only** starter you can open in **VS Code** and build with **CMake**.  
It opens a window, creates a GL context compatible with OpenGL 1.1 calls, and draws a spinning tri.

---

## TL;DR (Quick Start)

1. Install **VS Code** and the extensions: **C/C++**, **CMake Tools**, **CMake**.
2. Install **vcpkg** (dependency manager for C/C++).
3. In this folder, run:
   ```bash
   cmake --preset windows-vcpkg
   cmake --build --preset windows-vcpkg
   ./out/windows-vcpkg/sandbox.exe
   ```

> If you prefer not to use vcpkg yet, see **Manual SDL2 setup (no vcpkg)** below.

---

## Why vcpkg? (It feels like `package.json` for C/C++)

- `vcpkg.json` in this repo declares dependencies (here: just `sdl2`).  
- CMake + vcpkg (manifest mode) auto-installs the right headers/libs into a per-project vcpkg store.
- You don’t copy DLLs and headers into `C:\libs` anymore.
- This is the closest to the **Node/npm** model in the C/C++ world today.

### Installing vcpkg

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
setx VCPKG_ROOT %CD%
```

Then restart your terminal (so `%VCPKG_ROOT%` is visible).

---

## Building in VS Code

1. Open this folder in VS Code.
2. When prompted by CMake Tools, choose the **`windows-vcpkg`** preset.
3. Click **Build** (or run `cmake --build --preset windows-vcpkg`).  
   The executable appears under `out/windows-vcpkg/`.

### Running

- Press **F5** (launch config: *Run Sandbox*), or run the built `sandbox.exe` from a terminal.
- **Esc** or the window’s close button exits.

---

## CMake primer (just what you need)

- **Configure/Generate**: CMake reads `CMakeLists.txt` + presets and generates native build files (Ninja/MSBuild).
- **Build**: CMake then calls your chosen backend to compile/link targets.
- **Targets**: We define a static library `engine_core` and an app `sandbox` that links it.
- **Dependencies**: `find_package(SDL2)` resolves via vcpkg manifest to headers/libs; we also link `opengl32` on Windows.

Key files:
- `CMakeLists.txt` — project, targets, compile flags, platform options.
- `CMakePresets.json` — saved configurations (like “profiles”). The `windows-vcpkg` preset wires the vcpkg toolchain.
- `vcpkg.json` — your dependency manifest (like package.json).

---

## Manual SDL2 setup (no vcpkg)

1. Download **SDL2 development package** for MSVC (from libsdl.org).
2. Unzip to e.g. `external/SDL2-2.30.x`.
3. Add in `CMakeLists.txt` (replace the `find_package(SDL2)` block):
   ```cmake
   target_include_directories(sandbox PRIVATE ${CMAKE_SOURCE_DIR}/external/SDL2-2.30.x/include)
   if (MSVC)
     target_link_directories(sandbox PRIVATE ${CMAKE_SOURCE_DIR}/external/SDL2-2.30.x/lib/x64)
     target_link_libraries(sandbox PRIVATE SDL2 SDL2main opengl32)
     target_compile_definitions(sandbox PRIVATE SDL_MAIN_HANDLED)
   endif()
   ```
4. Copy `SDL2.dll` next to `sandbox.exe` after building (usually from the `lib/x64` folder).

---

## Where to put N64/Dreamcast later?

- `platforms/n64/` and `platforms/dreamcast/` are placeholders.  
- Keep their native **Makefiles** there and add CMake `add_custom_target()` like in the root `CMakeLists.txt` (already stubbed).

---

## Controls & behavior

- **Esc**: quit.
- The demo triangle rotates with a simple timer.

---

## Troubleshooting

- **CMake can’t find SDL2**: Ensure you used the `windows-vcpkg` preset (or installed SDL2 manually).
- **Link errors for OpenGL**: Make sure `opengl32` is linked (should be automatic on Windows).
- **Multiple SDL mains**: We define `SDL_MAIN_HANDLED` so your `main` works.

---

Happy hacking!
