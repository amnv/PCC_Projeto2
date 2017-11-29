all: compile
compile: 
	@mkdir -p bin
	@g++ -O3 -std=c++11 -I include src/*.cpp -o bin/ipmt
run:
	@bin/ipmt

