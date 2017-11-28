all: compile
compile: 
	@g++ -O3 -std=c++11 src/*.cpp -o bin/ipmt
run:
	@bin/ipmt

