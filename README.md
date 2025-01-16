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

Download w64devkit from https://github.com/skeeto/w64devkit/releases, extract and move to C\

Add to PATH C:\w64devkit\bin

This should enable g++ and make in powershell.

```
# Clone raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src

# Build
make PLATFORM=PLATFORM_DESKTOP

# Copy the built library and headers
cd ../..
cp raylib/src/raylib.h include/
cp raylib/src/libraylib.a lib/

# Optionally, add other raylib files
cp raylib/src/raymath.h include/
cp raylib/src/rlgl.h include/        # required for raygui
cp raylib/src/rcamera.h include/
# ...
```

Remove the repo if not planned to modify raylib source code.

```
rm -rf raylib
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
