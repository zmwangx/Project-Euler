CXX = g++-4.8
CXXFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O2 -std=c++11 -pedantic -m32
LDFLAGS = -m32 -fno-common
SOURCES = prime.h prime.cpp modulo.h modulo.cpp
OBJECTS = prime.o modulo.o
TARGETS = libnt.a

$(TARGETS) : $(OBJECTS)
	ar rcs libnt.a $(OBJECTS)

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
