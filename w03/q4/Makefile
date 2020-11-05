# Makefile


debug = DEBUG
out = Q4.exe


all : 
	gcc -o $(out) malloc.c

debug : 
	gcc -o $(out) -D$(debug) malloc.c

release : 
	gcc -o $(out) malloc.c

clean : 
	rm -f $(out)
