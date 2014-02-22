CC = clang
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter -std=c99 -pedantic -ftrapv -O2
LDFLAGS = -fno-common
SOURCES = 136.c
OBJECTS = $(SOURCES:.c=.o)
TARGETS = 136

$(TARGETS) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
