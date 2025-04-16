CXX          := g++
CXXFLAGS     := -g -std=c++17 -Wall -Wextra -I../include -I..
LDFLAGS      := -L/usr/lib -lstdc++ -lm
LDLIBS       := -lncursesw -pthread
TARGET       := tests

PROJECT_ROOT := ..
SRC_DIR      := $(PROJECT_ROOT)/src/logic
TEST_DIR     := .
CATCH_DIR    := $(PROJECT_ROOT)/libs

TEST_SRC     := $(TEST_DIR)/tests.cpp
APP_SRCS     := $(SRC_DIR)/ship_builder.cpp $(SRC_DIR)/board.cpp $(SRC_DIR)/ship.cpp
CATCH_SRC    := $(CATCH_DIR)/catch_amalgamated.cpp

all: $(TARGET)

$(TARGET): $(TEST_SRC) $(APP_SRCS) $(CATCH_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

test:
	./$(TARGET) --success -d yes

clean:
	rm -f $(TARGET)

.PHONY: all clean