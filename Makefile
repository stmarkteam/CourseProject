CC = g++
MO = ./build/main.o
MC = ./src/main.cpp
QQ = -lsfml-graphics -lsfml-window -lsfml-system

all: dc

dc: $(MO)
	mkdir -p bin
	$(CC) $(MO) -o ./bin/game $(QQ)

$(MO): $(MC)
	mkdir -p build
	$(CC) -c $(MC) -o $(MO) $(QQ)
clean:
	rm -rf build bin
