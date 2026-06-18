CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt

out.txt: main
	./$< > $@

main: main.o EVD.o matrix.o vector.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc EVD.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

matrix.o: matrix.cc matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

EVD.o: EVD.cc EVD.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f out.txt main *.o
