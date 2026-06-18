CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt

out.txt: main
	./$< > $@

main: main.o vec.o
	$(CXX) -o $@ $^

main.o: main.cc vec.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vec.o: vec.cc vec.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f out.txt main *.o
