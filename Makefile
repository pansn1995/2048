LIBS = -lncurses
2048:2048.cpp Game.cpp window.cpp
	g++  $^ -o $@ $(LIBS)

clean:
	rm 2048