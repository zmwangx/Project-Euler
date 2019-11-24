CC = clang++
CXXFLAGS = -std=c++14 -Wall -Werror

.PHONY: all clean

all: solution

prime: solution.o
	$(LINK.cc) $^ $(LDLIBS) -o $@

clean:
	@- $(RM) solution solution.o
