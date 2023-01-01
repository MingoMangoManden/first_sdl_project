make: clean build run

clean:
	rm -rf gun
	clear

build:
	gcc -Wall -g src/main.c -lSDL2 -o builds/gun

run:
	./gun
