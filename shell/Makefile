shell : src/main.c
	@mkdir -p bin
	@gcc -Wall -Werror --ansi --pedantic-errors -D_POSIX_C_SOURCE=200809L -o bin/ipiranga src/main.c src/printPrefix.c -lposixeg -Wl,-rpath='/usr/local/lib'

test : src/main.c
	@mkdir -p bin
	@gcc -o bin/ipiranga src/main.c src/printPrefix.c -lposixeg -Wl,-rpath='/usr/local/lib'

install :
	@cp bin/ipiranga /usr/bin
