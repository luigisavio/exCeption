
build: bin/final # produces executable file for the whole application, if not already produced

bin/final: bin/exCeption.o bin/exCeptionTests.o # links two object files to produce the executable file for the whole application. If the source files have been modified it automatically detects it and recompiles.
	@echo "-> linking"
	gcc bin/exCeption.o bin/exCeptionTests.o -o bin/final -g

bin/exCeption.o: exCeption.c # compiles (only, no linking) to produce object file for the library. gcc -c flag means do not link
	@echo "-> compiling exCeption.c"
	gcc -c exCeption.c -o bin/exCeption.o -g

bin/exCeptionTests.o: exCeptionTests.c # compiles (only, no linking) to produce object file for tests
	@echo "-> compiling exCeptionTests.c"
	gcc -c exCeptionTests.c -o bin/exCeptionTests.o -g

clean:
	@echo "-> cleaning bin folder"
	rm -f  bin/*