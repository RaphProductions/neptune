CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc -I/usr/include/freetype2 -g -ggdb -rdynamic
CPPFLAGS = -DBOOST_STACKTRACE_USE_ADDR2LINE

PLATFORM = LINUX

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
RES_DIR = res

SOURCES = $(shell find $(SRC_DIR) -iname "*.cpp")
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

EXECUTABLE = $(BIN_DIR)/neptune

LD_LIBS = \
	-lm

LD_LIBS_LINUX = \
	-lX11

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LD_LIBS) $(LD_LIBS_$(PLATFORM))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
