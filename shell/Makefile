shell : src/main.c
	mkdir -p bin
	gcc -Wall -Werror --ansi --pedantic-errors -D_POSIX_C_SOURCE=200809L -o bin/shell src/main.c src/init.c -lposixeg -Wl,-rpath='/usr/local/lib' 

test : src/main.c
	mkdir -p bin
	gcc -o bin/shell src/main.c src/init.c -lposixeg -Wl,rpath='/usr/local/lib'
