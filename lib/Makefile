CXX = g++-4.8
CXXFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O2 -std=c++11 -pedantic -m32
LDFLAGS = -m32 -fno-common
SOURCES = prime.h prime.cpp modulo.h modulo.cpp random.h random.cpp numbers.h numbers.cpp
OBJECTS = prime.o modulo.o random.o
TARGETS = libnt.a librand.a

all : nt rand

nt : prime.h prime.cpp prime.o modulo.h modulo.cpp modulo.o numbers.h numbers.cpp numbers.o
	ar rcs libnt.a prime.o modulo.o numbers.o
rand : random.h random.cpp random.o
	ar rcs librand.a random.o


.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
