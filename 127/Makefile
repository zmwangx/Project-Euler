CC = clang
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic -ftrapv -O2
LDFLAGS = -fno-common
OBJECTS = 127.o decide-range.o
TARGETS = 127 decide-range

127 : 127.o
	$(CC) $(CFLAGS) -o 127 127.o $(LDFLAGS)

decide-range : decide-range.o
	$(CC) $(CFLAGS) -o decide-range decide-range.o $(LDFLAGS)

127.o : 127.c read-rad.h
	$(CC) $(CFLAGS) -c 127.c

decide-range.o : decide-range.c read-rad.h
	$(CC) $(CFLAGS) -c decide-range.c

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
