# Compiler
CC = g++

# Flags 
CC_FLAGS = -g -Iinclude -c

all: main

main: main.o review.o timer.o menu.o hash.o sort.o
		$(CC) -o bin/main.exe obj/main.o obj/Review.o obj/Sort.o obj/Timer.o obj/Menu.o obj/Hash.o

main.o: src/main.cpp
		$(CC) $(CC_FLAGS) src/main.cpp -o obj/main.o

review.o: src/Review.cpp include/Review.h
		$(CC) $(CC_FLAGS) src/Review.cpp -o obj/Review.o

hash.o: src/Hash.cpp include/Hash.h
		$(CC) $(CC_FLAGS) src/Hash.cpp -o obj/Hash.o

sort.o: src/Sort.cpp include/Sort.h
		$(CC) $(CC_FLAGS) src/Sort.cpp -o obj/Sort.o

timer.o: src/Timer.cpp include/Timer.h
		$(CC) $(CC_FLAGS) src/Timer.cpp -o obj/Timer.o

menu.o: src/Menu.cpp include/Menu.h
		$(CC) $(CC_FLAGS) src/Menu.cpp -o obj/Menu.o


execute: all
		./bin/main.exe