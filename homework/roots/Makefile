CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt

out.txt: main
	./$< > $@

main: main.o roots.o QR.o matrix.o vector.o
	$(CXX) -o $@ $^

main.o: main.cc roots.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

roots.o: roots.cc roots.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

QR.o: QR.cc QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

matrix.o: matrix.cc matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f out.txt main *.o