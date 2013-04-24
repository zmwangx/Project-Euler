CC = gcc-4.8
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O2 -std=c99 -pedantic -m32
LDFLAGS = -m32 -fno-common
SOURCES = 122.c
OBJECTS = $(SOURCES:.c=.o)
TARGETS = 122

$(TARGETS) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
