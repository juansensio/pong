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
SRCS = $(wildcard src/*.cpp) $(wildcard src/scenes/*.cpp)
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

