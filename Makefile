# Define variables for compiler, compiler flags, and library paths
CXX = clang++
CXXFLAGS = -Wall -I./include # Adjust the include path to your project structure
LDFLAGS = -L./lib -lraylib -lm # Adjust the library path if necessary

# Target for building the executable
tankTrouble: main.cpp Entity.cpp Tank.cpp Player1.cpp Player2.cpp Projectile.cpp TrapBase.cpp TrapVariant.cpp WallSet.cpp Trapdoor.cpp
	$(CXX) main.cpp Entity.cpp Tank.cpp Player1.cpp Player2.cpp Projectile.cpp TrapBase.cpp TrapVariant.cpp WallSet.cpp Trapdoor.cpp -o tankTrouble $(CXXFLAGS) $(LDFLAGS)
	./tankTrouble

# Target for cleaning up generated files
clean:
	rm -f tankTrouble
