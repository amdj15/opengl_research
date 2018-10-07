CC=clang++

PRGNAME=booom

# library search directory
LIBDIR=-L vendors/libs

# library names
LIBNAME=-lGLEW -lglfw3 -lassimp -lirrxml -lzlibstatic \
				-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# includes for libraries
INCLUDES=-I vendors

# -MMD flag allow to create .d files
CFLAGS=-c -Wall -std=c++14 -fvisibility=hidden -MMD

DEFINE=-D GLEW_STATIC -D STB_IMAGE_IMPLEMENTATION

DIST=bin
SRC=src
OBJ=build

SOURCE_FILES=$(wildcard $(SRC)/app/*.cpp) \
						 $(wildcard $(SRC)/loaders/*.cpp) \
						 $(wildcard $(SRC)/devices/opengl/*.cpp) \
						 $(wildcard $(SRC)/graphic/api/*.cpp) \
						 $(wildcard $(SRC)/graphic/*.cpp) \
						 $(wildcard $(SRC)/*.cpp)

OBJECT_FILES=$(SOURCE_FILES:%.cpp=$(OBJ)/%.o)
DEP_FILES=$(OBJECT_FILES:%.o=%.d)

EXECUTABLE=$(PRGNAME:%=$(DIST)/%)

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT_FILES)
	mkdir -p $(DIST)
	$(CC) $(LIBNAME) $(LIBDIR) -o $@ $^
	cp -a resources/. $(DIST)/
	cp -a src/shaders $(DIST)/shaders/

# Include all .d files
-include $(DEP_FILES)

$(OBJECT_FILES): $(OBJ)/%.o: %.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE) $< -o $@

clean:
	rm -rf *.o $(DIST) $(OBJ)
