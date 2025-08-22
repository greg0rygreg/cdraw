cf = -g -Wall -Wextra
c = gcc $(cf)
ifeq ($(OS), Windows_NT)
	del = del /Q
	e = .exe
else
	del = rm -f
	e = 
endif

all: main

main:
	$(c) -o main main.c libs/libmenuR.c libs/libdraw.c libs/strutils.c
