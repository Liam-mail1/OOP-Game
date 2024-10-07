tankTrouble: main.cpp Entity.cpp Tank.cpp Player1.cpp Player2.cpp Projectile.cpp
	clang++ main.cpp Entity.cpp Tank.cpp Player1.cpp Player2.cpp Projectile.cpp -o tankTrouble -Wall -lraylib -lm;
	./tankTrouble

clean:
	rm tankTrouble