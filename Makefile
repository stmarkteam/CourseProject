CC = g++
MO = ./build/src/main.o
MC = ./src/main.cpp
QQ = -lsfml-graphics -lsfml-window -lsfml-system
MT = ./test/main_test.cpp
FT = ./test/function_test.cpp
MTO = ./build/test/main_test.o
FTO = ./build/test/function_test.o

all: game test

game: $(MO)
	mkdir -p bin
	$(CC) $(MO) -o ./bin/game $(QQ)

test: $(MTO) $(FTO)
	$(CC) $(MTO) $(FTO) -o ./bin/test $(QQ)

$(MO): $(MC)
	mkdir -p build/src
	$(CC) -c $(MC) -o $(MO) $(QQ)

$(MTO): $(MT)
	mkdir -p build/test
	$(CC) -c $(MT) -o $(MTO) $(QQ)

$(FTO): $(FT)
	$(CC) -c $(FT) -o $(FTO) $(QQ)

clean:
	rm -rf build bin
