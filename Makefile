cf = -g -Wall -Wextra
c = clang $(cf)
ifeq ($(OS), Windows_NT)
	del = del /Q
	e = .exe
else
	del = rm -f
	e = 
endif

all: main clean

main: libmenu.o strutils.o main.o libdraw.o
	$(c) -o main libmenu.o strutils.o main.o libdraw.o

main.o:
	$(c) -c main.c

libmenu.o:
	$(c) -c libs/libmenu.c -o libmenu.o

strutils.o:
	$(c) -c libs/strutils.c -o strutils.o

libdraw.o:
	$(c) -c libs/libdraw.c -o libdraw.o

clean:
	$(del) *.o
