CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDLIBS := -lncursesw -pthread
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := battleship
INCLUDE  := -Iinclude/
SRC      :=                        \
   $(wildcard src/scenes/*.cpp)    \
   $(wildcard src/ui/*.cpp)        \
   $(wildcard src/base/*.cpp)      \
   $(wildcard src/logic/*.cpp)     \
   $(wildcard src/*.cpp)           \

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
         := $(OBJECTS:.o=.d)

AUXFILES  = ./

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@ $(LDLIBS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS) $(LDLIBS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release 

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*