# Instalación `raylib`

Puedes instalar `raylib` en Windows, macOS y Linux siguiendo los siguientes pasos.

```
# Clonar raylib
git clone https://github.com/raysan5/raylib.git
cd raylib/src

# Build
make PLATFORM=PLATFORM_DESKTOP

# Copiar librería y headers
cd ../..
cp raylib/src/raylib.h include/
cp raylib/src/libraylib.a lib/

# Opcionalmente, añadir otros archivos de raylib
cp raylib/src/raymath.h include/
cp raylib/src/rlgl.h include/        # required for raygui
cp raylib/src/rcamera.h include/
# ...
```

Para ello, en función del sistema operativo, seguir los siguientes pasos.

## En Windows

Descargar `w64devkit` de https://github.com/skeeto/w64devkit/releases, extraer y mover a `C:\`

Añadir `C:\w64devkit\bin` en el `PATH` para tener acceso a `g++` y `make` en terminal.

## En macOS

Instalar `xcode-select` para tener acceso a `g++` y `make` en terminal.

```
# Instalar Xcode Command Line Tools si no lo tienes ya
xcode-select --install
```

## Multiplataforma (Windows + macOS)

El siguiente proceso es útil para poder trabajar en un mismo proyecto tanto en Windows como en macOS/Linux.

En Windows, seguir los pasos anteriores.

En macOS, instalar `Homebrew` y `CMake` usando Homebrew.

```
# Instalar Homebrew si no lo tienes ya

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install CMake using Homebrew

brew install cmake
```

Luego instala `raylib` de la siguiente manera:

```
# Clonar raylib

git clone https://github.com/raysan5/raylib.git
cd raylib

# Build

mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
```

Esto instalará `raylib` en `usr/local/lib` y `usr/local/include`.

Puedes ver en el `Makefille` como se ha configurado el proyecto para que se compile tanto en Windows como en macOS.

# Instalación `raygui`

```
git clone https://github.com/raysan5/raygui.git
cp raygui/src/*.h include/
rm -rf raygui
```
