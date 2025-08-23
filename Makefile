cf = -g -Wall -Wextra
c = gcc $(cf)
ifeq ($(OS), Windows_NT)
	e = .exe
else
	e = 
endif

all:
	$(c) -o main$(e) main.c libs/libmenu.c libs/libdraw.c libs/strutils.c
