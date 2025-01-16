# Use different extension for Windows executables
ifeq ($(OS),Windows_NT)
    EXT = .exe
    INCLUDES = -I./include
    LDFLAGS = -L./lib
    LIBS = -lraylib -lgdi32 -lwinmm
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
CFLAGS = -Wall -std=c++20

# On Windows, we need additional libraries
ifeq ($(OS),Windows_NT)
    LIBS += -lopengl32 -lgdi32 -lwinmm
endif

TARGET = game$(EXT)
SRCS = src/*.cpp 

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LDFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(TARGET)

run:
	./$(TARGET)