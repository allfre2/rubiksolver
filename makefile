
CC = gcc
CFLAGS = -std=c99 -O2 -Wall -fcommon -w
POSIXTHREADS = -lpthread
OBJS = main.o common.o
WORKINGDIR = ./bin
OUT= $(WORKINGDIR)/unisolver
SOURCES = main.c common.c 
RM = rm

default: resetenv unisolver removebinaries

resetenv:
	if [ -d $(WORKINGDIR) ]; then rm -rf $(WORKINGDIR); fi

unisolver: $(OBJS) 
	mkdir $(WORKINGDIR)
	@$(CC) $(CFLAGS) -o $(OUT) $(OBJS) $(POSIXTHREADS) 

win32: 
	i686-w64-mingw32-gcc -o $(OUT)32.exe $(CFLAGS) $(SOURCES)

win64: 
	x86_64-w64-mingw32-gcc -o $(OUT)64.exe $(CFLAGS) $(SOURCES)

removebinaries:
	rm *.o

clean: resetenv removebinaries

all: resetenv unisolver win32 win64 removebinaries

install: 
	@sudo cp $(OUT)/* /usr/bin
