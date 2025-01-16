Install raylib

on mac

```
# Install Xcode Command Line Tools if you haven't already
xcode-select --install

# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install CMake using Homebrew
brew install cmake

# Clone the raylib repository
git clone https://github.com/raysan5/raylib.git
cd raylib

# Build raylib using CMake
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

on windows

```
# Clone raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src

# Build using mingw32-make
mingw32-make PLATFORM=PLATFORM_DESKTOP

# Copy the built library and headers
copy /Y raylib.h C:\msys64\mingw64\include
copy /Y *.h C:\msys64\mingw64\include
copy /Y librarylib.a C:\msys64\mingw64\lib
```

on both, then

```

```

Remove the repo if not planned to modify raylib source code.

Troubleshooting:

If you get linking errors, make sure raylib was installed correctly by checking:

```
ls /usr/local/lib/libraylib*
ls /usr/local/include/raylib.h
```

If the library isn't found, you might need to update your dynamic library path:

```
pkg-config: command not found
```

If you're using VS Code, you might want to add these include paths to your c_cpp_properties.json:

```
 {
       "includePath": [
           "${workspaceFolder}/**",
           "/usr/local/include"
       ]
   }
```

Intalling imgui and rlImGui

```
# clone repos
git clone https://github.com/raylib-extras/rlImGui.git
git clone https://github.com/ocornut/imgui.git

mkdir include

cp rlImGui/*.h include/
cp rlImGui/*.cpp src/
cp -r rlImGui/extras include/

cp imgui/*.h include/
cp imgui/*imgui*.cpp src/

rm -rf imgui
rm -rf rlImGui
```

Installing raygui

```
git clone https://github.com/raysan5/raygui.git
cp raygui/src/*.h include/
rm -rf raygui
```
