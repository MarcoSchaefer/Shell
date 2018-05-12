shell : src/shell.c
	mkdir -p bin
	gcc -Wall -Werror --ansi -L/usr/local/lib -lposixeg --pedantic-errors -D_POSIX_C_SOURCE=200809L -o bin/shell src/shell.c
