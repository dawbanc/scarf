all:

clean:
	@rm scarf

build:
	g++ -Wall -fPIC -I${PWD}/src/cpp -o scarf src/cpp/main.cpp

run:
	./scarf
