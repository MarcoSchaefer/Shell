shell : src/main.c src/printPrefix.c src/signalHandler.c src/builtinCommand.c
	@clear
	@mkdir -p bin
	@gcc -Wall -Werror --ansi --pedantic-errors -D_POSIX_C_SOURCE=200809L -o bin/ipiranga src/main.c src/printPrefix.c src/signalHandler.c src/builtinCommand.c -lposixeg -Wl,-rpath='/usr/local/lib'

install :
	@mkdir -p bin
	@gcc -Wall -Werror --ansi --pedantic-errors -D_POSIX_C_SOURCE=200809L -o bin/ipiranga src/main.c src/printPrefix.c src/signalHandler.c src/builtinCommand.c -lposixeg -Wl,-rpath='/usr/local/lib'
	@cp bin/ipiranga /usr/bin
