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

# Recursive wildcard function to find all .cpp files in src/ directory and subdirectories
rwildcard = $(foreach d,$(wildcard $1*), \
	$(if $(wildcard $d/),$(call rwildcard,$d/,$2),) \
	$(filter $(subst *,%,$2),$d))

# Define the source files by finding all .cpp files recursively
SRCS := $(call rwildcard,src/,*.cpp)

# Generate object files from source files
OBJS := $(SRCS:.cpp=.o)

# Create output directories
OBJDIRS := $(sort $(dir $(OBJS)))
$(shell mkdir -p $(OBJDIRS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

# Pattern rule for object files
%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

mac: clean all
	@rm -rf pong.app
	@mkdir -p pong.app/Contents/MacOS
	@mkdir -p pong.app/Contents/Resources
	@cp $(TARGET) pong.app/Contents/MacOS/
	@cp assets.txt pong.app/Contents/Resources/
	@cp -r assets pong.app/Contents/Resources/
	@cp Info.plist pong.app/Contents/

windows: clean all
	@rm -rf dist
	@mkdir -p dist/pong
	@cp $(TARGET) dist/pong/
	@cp -r assets dist/pong/
	@cp assets.txt dist/pong/
	@powershell Compress-Archive -Path "dist/*" -DestinationPath "pong.zip" -Force

