CXX = g++-4.8
CXXFLAGS = -g -Wall -Wextra -Wno-unused-parameter -O2 -std=c++11 -pedantic -m32
LDFLAGS = -m32
SOURCES = 381.cpp ../Library/prime.cpp ../Library/modulo.cpp
OBJECTS = 381.o ../Library/prime.o ../Library/modulo.o
TARGETS = 381

$(TARGETS) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
../Library/modulo.o : ../Library/modulo.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ ../Library/modulo.cpp $(LDFLAGS)
../Library/prime.o : ../Library/prime.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ ../Library/prime.cpp $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(TARGETS) $(OBJECTS) core
