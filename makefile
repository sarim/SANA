CC = gcc
CFLAGS = -lcurl
TARGETS = mainfile.sana.c functions.sana.c

all : $(TARGETS)
	gcc mainfile.sana.c functions.sana.c -o SANA -lcurl
