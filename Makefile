# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11
SRC = ./src/main.cc
OBJ = $(SRC:.cc=.o)
EXEC = HW4

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling
.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(EXEC)t