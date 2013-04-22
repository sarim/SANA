CC = clang
TARGETS = regex.c mainfile.sana.c functions.sana.c
CFLAGS = -lcurl

all : $(TARGETS)
	$(CC) -o SANA $(TARGETS) $(CFLAGS)
