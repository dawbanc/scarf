all:

clean:
	@rm scarf

build:
	g++ -o scarf src/cpp/main.cpp

run:
	./scarf
