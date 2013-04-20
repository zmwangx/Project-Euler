CXX = g++-4.8
CXXFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O2 -std=c++11 -pedantic -m32
LDFLAGS = -m32
SOURCES = 131.cpp ../Library/prime.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGETS = 131

$(TARGETS) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
