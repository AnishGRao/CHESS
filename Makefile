
all:
	g++ -O3 pieces.h chess.cpp -o chess.o; ./chess.o
debug:
	g++ -g pieces.h chess.cpp -o chess_debug.o;

clean:
	rm *.o
