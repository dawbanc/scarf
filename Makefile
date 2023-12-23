all:

clean:
	@rm scarf

build:
	g++ -Wall -fPIC -o scarf src/cpp/main.cpp

run:
	./scarf
