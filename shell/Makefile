shell : src/main.c
	mkdir -p bin
	gcc -Wall -Werror --ansi -L/usr/local/lib -lposixeg --pedantic-errors -D_POSIX_C_SOURCE=200809L -o bin/shell src/main.c src/init.c

test : src/main.c
	mkdir -p bin
	gcc -L/usr/local/lib -lposixeg -o bin/shell src/main.c src/init.c
