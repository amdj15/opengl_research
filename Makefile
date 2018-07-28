CC=clang++

PRGNAME=booom

# library search directory
LIBDIR=-L vendors/libs

# library names
LIBNAME=-lGLEW -lglfw3 -lassimp -lirrxml -lzlibstatic \
				-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# includes for libraries
INCLUDES=-I vendors

CFLAGS=-c -Wall -std=c++14

DEFINE=-D GLEW_STATIC -D STB_IMAGE_IMPLEMENTATION

DIST=./bin
FILES=*.cpp

all: compile
	mkdir -p $(DIST)
	cp -a resources/. $(DIST)/
	$(CC) $(LIBNAME) $(LIBDIR) -o $(DIST)/$(PRGNAME) *.o

compile:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE) src/loaders/$(FILES) src/$(FILES)

clean:
	rm -rf *.o $(DIST)
