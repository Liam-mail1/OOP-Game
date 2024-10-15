# Define variables for compiler, compiler flags, and library paths
CXX = clang++
CXXFLAGS = -Wall -g -O0 -I./include  # Include paths for your headers
LDFLAGS = -L./lib -lraylib -lm        # Linker flags for libraries

# Source files for the main executable
SRC_FILES = src/main.cpp src/Entity.cpp src/Tank.cpp src/Player1.cpp src/Player2.cpp src/Projectile.cpp src/TrapBase.cpp src/TrapVariant.cpp src/WallSet.cpp src/Trapdoor.cpp src/MainMenu.cpp

# Object files for the main executable
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Target for building the main executable
tankTrouble: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)  # Use $@ for target name
	./$@  # Run the executable after building

# Target for building the test executable for Player1
test_player1: test/test_player1.cpp src/Player1.cpp src/Tank.cpp src/Projectile.cpp src/Entity.cpp
	$(CXX) test/test_player1.cpp src/Player1.cpp src/Tank.cpp src/Projectile.cpp src/Entity.cpp -o $@ $(CXXFLAGS) $(LDFLAGS)


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
