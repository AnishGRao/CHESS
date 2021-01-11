
all:
	g++ -O3 -ldl -pthread pieces.h chess.cpp -o chess.o; ./chess.o
debug:
	g++ -g -ldl -pthread pieces.h chess.cpp -o chess_debug.o;

clean:
	rm *.o
