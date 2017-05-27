CC = g++
MO = ./build/main.o
MC = ./src/main.cpp
QQ = -lsfml-graphics -lsfml-window -lsfml-system
MT = ./test/main_test.cpp
FT = ./test/function_test.cpp
MTO = ./build/main_test.o
FTO = ./build/function_test.o

all: game test

game: $(MO)
	mkdir -p bin
	$(CC) $(MO) -o ./bin/game $(QQ)

test: $(MTO) $(FTO)
	$(CC) $(MTO) $(FTO) -o ./bin/test $(QQ)

$(MO): $(MC)
	mkdir -p build
	$(CC) -c $(MC) -o $(MO) $(QQ)

$(MTO): $(MT)
	$(CC) -c $(MT) -o $(MTO) $(QQ)

$(FTO): $(FT)
	$(CC) -c $(FT) -o $(FTO) $(QQ)

clean:
	rm -rf build bin
