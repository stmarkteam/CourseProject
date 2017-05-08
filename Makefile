CC = g++
MO = ./build/main.o
MC = ./src/main.cpp
QQ = -lsfml-graphics -lsfml-window -lsfml-system

all: dc

dc: $(MO)
	$(CC) $(MO) -o ./bin/game $(QQ)

$(MO): $(MC)
	$(CC) -c $(MC) -o $(MO) $(QQ)
clean:
	rm ./build/*.o
