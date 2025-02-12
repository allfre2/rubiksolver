
CC = gcc
CFLAGS = -std=c99 -O2 -Wall -fcommon -w
OBJS = main.o common.o solver.o
WORKINGDIR = ./bin
OUT= $(WORKINGDIR)/rubiksolver
SOURCES = main.c common.c  solver.c
RM = rm

default: resetenv rubiksolver removebinaries

resetenv:
	if [ -d $(WORKINGDIR) ]; then rm -rf $(WORKINGDIR); fi

rubiksolver: $(OBJS) 
	mkdir $(WORKINGDIR)
	@$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

win32: 
	i686-w64-mingw32-gcc -o $(OUT)32.exe $(CFLAGS) $(SOURCES)

win64: 
	x86_64-w64-mingw32-gcc -o $(OUT)64.exe $(CFLAGS) $(SOURCES)

removebinaries:
	rm *.o

clean: resetenv removebinaries

all: resetenv rubiksolver win32 win64 removebinaries

install: 
	@sudo cp $(OUT)/* /usr/bin
