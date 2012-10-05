CC = gcc
CFLAGS = -lcurl
TARGETS = mainfile.sana.c functions.sana.c

all : $(TARGETS)
	$(CC) $(TARGETS) -o SANA $(CFLAGS)
