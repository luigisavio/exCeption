COMPILER_FLAGS = -g -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Werror

# WARNING this flag enables multi thread compile. This only works if dependencies are declared correctly in this file
MAKEFLAGS += -j4 

# Produces executable file for the whole application, if not already produced
build: bin/final 

# Links two object files to produce the executable file for the whole application. If the source files have been 
# modified it automatically detects it and recompiles.
bin/final: bin/exCeption.o bin/exCeptionTests.o 	
	@echo "-> linking"
	gcc bin/exCeption.o bin/exCeptionTests.o -o bin/final $(COMPILER_FLAGS)

# Compiles (only, no linking) to produce object file for the library. gcc -c flag means do not link
bin/exCeption.o: exCeption.c exCeption.h	
	@echo "-> compiling exCeption.c"
	gcc -c exCeption.c -o bin/exCeption.o $(COMPILER_FLAGS)

# Compiles (only, no linking) to produce object file for tests
bin/exCeptionTests.o: exCeptionTests.c exCeption.c exCeption.h
	@echo "-> compiling exCeptionTests.c"
	gcc -c exCeptionTests.c -o bin/exCeptionTests.o $(COMPILER_FLAGS)

clean:
	@echo "-> cleaning bin folder"
	rm -f  bin/*
