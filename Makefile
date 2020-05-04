all: main

main: bin/main
 
bin/main: build/main.o build/board.o build/board_print.o
	gcc -Wall -Werror build/main.o build/board.o build/board_print.o -o bin/main
 
build/main.o: src/main.cpp
	gcc -I includes -Wall -lncurses -ltinfo -Werror -c src/main.cpp -o build/main.o
 
build/board.o: src/board.cpp  src/board_print.cpp
	gcc -Wall -Werror -c src/board.cpp -o build/board.o
 
build/board_print.o: src/board_print.cpp
	gcc -Wall -Werror -c src/board_print.cpp -o build/board_print.o
 
.PHONY : clean
clean:
	rm -rf build/*.o
