cmake_minimum_required(VERSION 3.0)
project(MyRaylibGame)

# If you installed raylib system-wide on macOS (via brew) or MSYS2, 
# you can find the package via:
find_package(raylib REQUIRED)

# Alternatively, if raylib can’t be found automatically, you might need:
# set(RAYLIB_ROOT "/usr/local/") # or wherever raylib is found
# find_package(raylib REQUIRED HINTS "${RAYLIB_ROOT}")

add_executable(${PROJECT_NAME} src/main.cpp)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

# On Windows, you might need to link additional libraries:
if (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32 gdi32 winmm)
endif()
