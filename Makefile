# Use different extension for Windows executables
ifeq ($(OS),Windows_NT)
    EXT = .exe
else
    EXT =
endif

CC = g++
CFLAGS = -Wall -std=c++11
INCLUDES = -I/usr/local/include -I./include
LDFLAGS = -L/usr/local/lib
LIBS = -lraylib

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