# Makefile

CC = gcc
EXE = calc.exe
OBJS = calc.o add.o sub.o mul.o

all : $(EXE)

$(EXE) : $(OBJS)
	$(CC) -o $(EXE) $(OBJS)

calc.o : calc.c
	$(CC) -c calc.c

add.o : add.c
	$(CC) -c add.c

sub.o : sub.c
	$(CC) -c sub.c

mul.o : mul.c
	$(CC) -c mul.c

clean :
	rm -f $(OBJS)
