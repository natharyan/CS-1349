# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Executable name (defaults to "output" if not specified)
EXEC = $(FILENAME)

# Target: all
all: $(EXEC)

# Rule to compile the executable
$(EXEC): $(EXEC).cpp
    $(CXX) $(CXXFLAGS) -o $@ $^

# Target: clean
clean:
    rm -f $(EXEC)