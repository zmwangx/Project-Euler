CXX = g++-4.8
CXXFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O2 -std=c++11 -pedantic -m32
LDFLAGS = -m32 -fno-common -L../lib/ -lnt
SOURCES = 187.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGETS = 187

$(TARGETS) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
