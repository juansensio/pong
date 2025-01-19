ifeq ($(OS),Windows_NT)
    EXT = .exe
    INCLUDES = -I./include
    LDFLAGS = -L./lib
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
else
    EXT =
    INCLUDES = -I/usr/local/include -I./include
    LDFLAGS = -L/usr/local/lib -L./lib
    # Add rpath for macOS
    ifeq ($(shell uname),Darwin)
        LDFLAGS += -Wl,-rpath,/usr/local/lib
    endif
    LIBS = -lraylib
endif

CC = g++
CFLAGS = -Wall -std=c++20 -O3 -Wno-unused-result

TARGET = main$(EXT)
ifeq ($(OS),Windows_NT)
    SRCS = $(subst /,\,$(shell dir /s /b src\*.cpp))
else
    SRCS = $(shell find src -name "*.cpp")
endif
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

mac: clean all
	@mkdir -p pong.app/Contents/MacOS
	@mkdir -p pong.app/Contents/Resources
	@cp $(TARGET) pong.app/Contents/MacOS/
	@cp assets.txt pong.app/Contents/Resources/
	@cp -r assets pong.app/Contents/Resources/
	@cp Info.plist pong.app/Contents/

dmg: 
    hdiutil create -size 32m -fs HFS+ -volname "Pong" pong_writeable.dmg
    hdiutil attach pong_writeable.dmg
    hdiutil convert pong_writeable.dmg -format UDZO -o pong.dmg


windows: $(TARGET)
	@mkdir -p dist
	@cp $(TARGET) dist/
	@cp -r assets dist/

