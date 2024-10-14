# Define variables for compiler, compiler flags, and library paths
CXX = clang++
CXXFLAGS = -Wall -g -O0 -I./include  # Include paths for your headers
LDFLAGS = -L./lib -lraylib -lm        # Linker flags for libraries

# Source files for the main executable
SRC_FILES = main.cpp Entity.cpp Tank.cpp Player1.cpp Player2.cpp Projectile.cpp TrapBase.cpp TrapVariant.cpp WallSet.cpp Trapdoor.cpp

# Object files for the main executable
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Target for building the main executable
tankTrouble: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)  # Use $@ for target name
	./$@  # Run the executable after building

# Target for building the test executable for Player1
test_player1: test_player1.cpp Player1.cpp Tank.cpp Projectile.cpp Entity.cpp
	$(CXX) test_player1.cpp Player1.cpp Tank.cpp Projectile.cpp Entity.cpp -o $@ $(CXXFLAGS) $(LDFLAGS)


# Compile all source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target for cleaning up generated files
clean:
	rm -f $(OBJ_FILES) tankTrouble test_player1 test_trap

# Target to run all tests
run_tests: test_player1 # Run the tests
	./test_player1  # Run the test executable

.PHONY: clean run_tests
