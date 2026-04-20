CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt

out.txt: main
	./$< > $@

main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc vec_template.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Ingen vec_template.o fordi en header-fil ikke skal kompileres.

clean:
	rm -f main out.txt *.o