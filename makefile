build: exCeptionTests.c
	gcc -o bin/exCeption exCeptionTests.c exCeption.c

clean:
	rm -f  bin/*