# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
SRC = ./src/main.cc
OBJ = $(SRC:.cc=.o)
EXEC = HW4
DEBUG_EXEC = HW4_debug

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Debug target
debug: CXXFLAGS += -DDEBUG -g
debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling
.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(EXEC) $(DEBUG_EXEC)

# Run release build
run: $(EXEC)
	./$(EXEC)