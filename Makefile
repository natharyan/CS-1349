# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

EXECS = DFA Turing

# Executable name (defaults to "output" if not specified)
# FILENAME=DFA
# EXEC=$(FILENAME)

# Target: all
# all: $(EXEC)

# *.o: *.cpp
	# $(CXX) $(CXXFLAGS) -c $^

# Rule to compile the executable
# $(EXEC): $(EXEC).cpp
	# $(CXX) $(CXXFLAGS) -o $@ $^

# Target: clean
clean:
	rm -f *.o $(EXECS)

.PHONY: all clean