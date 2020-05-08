all: test

main: bin/main

test: bin/main-test

bin/main: build/main.o build/board.o build/board_print.o
	gcc -Wall -Werror build/main.o build/board.o build/board_print.o -o bin/main

bin/main-test: build/main-test.o build/board.o build/board_print.o
	gcc build/main-test.o  build/board.o build/board_print.o -o bin/main-test

build/main-test.o: test/main-test.c
	gcc -I thirdparty -I src -c test/main-test.c -o build/main-test.o

build/main.o: src/main.c
	gcc -I includes -Wall -lncurses -ltinfo -Werror -c src/main.c -o build/main.o
 
build/board.o: src/board.c
	gcc -Wall -Werror -c src/board.c -o build/board.o
 
build/board_print.o: src/board_print.c
	gcc -Wall -Werror -c src/board_print.c -o build/board_print.o
 
.PHONY : clean
clean:
	rm -rf build/*.o
