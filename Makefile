SDL=/opt/local
CXX = g++
CFLAGS = -std=c++14 -g -Wall -L/opt/local/lib -I/opt/local/include

%.o : %.cpp %.hpp
	$(CXX) -c $(CFLAGS) $< -lSDL2
game.exe: main.o bullet.o player.o enemy.o
	$(CXX) -o $@ $^ -L$(SDL)/lib -lm -lSDL2

clean:
	$(RM) $(wildcard *.exe) $(wildcard *.o) $(wildcard *.exe)
