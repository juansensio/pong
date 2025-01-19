En este repo encontrarás código de muestra para crear un juego 2D con `raylib` en C++.

La arquitectura del juego sigue el patrón ECS (Entity Component System) y lo he desarrollado a partir de los siguientes recursos:

- https://www.youtube.com/playlist?list=PL_xRyXins84_Sq7yZkxGP_MgYAH-Zo8Uu
- https://github.com/raysan5/raylib

Puedes encontrar videos con el proceso de desarrollo en mi canal de YouTube: https://www.youtube.com/@janusnoise

# Instalación `raylib`

Puedes instalar `raylib` en Windows, macOS y Linux de diferentes maneras, y encontrarás multitud de tutoriales online de cómo hacerlo. Sin embargo, el sistema más sencillo y portable que he encontrado es siguiendo los siguientes pasos. Además, de esta manera, podrás modificar el código fuente de `raylib` para adaptarlo a tus necesidades (corregir bugs, añadir funcionalidades, optimizaciones, etc.).

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

Para ello necesitarás tener instalado `g++` y `make` en tu sistema, y en función del sistema operativo tendrás que seguir los siguientes pasos.

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

Puedes ver en el `Makefille` como se ha configurado el proyecto para que se compile tanto en Windows como en macOS, usando `raylib` de la carpeta `lib` y `include` en windows y `raylib` de la carpeta `usr/local/lib` y `usr/local/include` en macOS.

# Instalación `raygui`

En cualquier plataforma, puedes instalar `raygui` de la siguiente manera:

```
git clone https://github.com/raysan5/raygui.git
cp raygui/src/*.h include/
rm -rf raygui
```

# Arquitectura

- [assets](assets): Recursos del juego.
- [include](include): Cabeceras de las librerías externas.
- [lib](lib): Librería de raylib.
- [src](src): Código fuente del juego.
  - [main.cpp](src/main.cpp): Punto de entrada del juego
  - [GameEngine.h](src/GameEngine.h): Bucle principal del juego, manejo de escenas, assets, configuración, settings, ...
  - [scenes](src/scenes): Escenas del juego, con los sistemas para trabajar con entidades y objetos (movimiento, colisiones, renderizado, ...)
    - [objects](src/scenes/objects): Objetos del juego (jugador, enemigos, ...)
    - [entities](src/scenes/entities): Funcionalidad para crear entidades y objectos
      - [components](src/scenes/entities/components): Componentes de las entidades

# Publicación

## macOS

Para publicar el juego en macOS, puedes usar el siguiente comando:

```
make mac
```

Esto creará un archivo `.app` que puedes ejecutar directamente.

Para crear un archivo `.dmg` que puedas distribuir, seguir los siguientes pasos:

```
hdiutil create -size 32m -fs HFS+ -volname "My App" my_app_writeable.dmg
hdiutil attach my_app_writeable.dmg
```

Arrastra tu aplicación al dmg que aparece en el escritorio. Luego ejecuta esto, reemplazando disk999 con el /dev/disk que se especificó en el paso anterior.

```
hdiutil detach /dev/disk999
hdiutil convert my_app_writeable.dmg -format UDZO -o my_app.dmg
```
