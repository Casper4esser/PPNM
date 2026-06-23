CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: plot.svg

plot.svg: plot.gpi data.txt
	gnuplot $<

data.txt: main
	./$<

main: main.o ann.o minimization.o QR.o matrix.o vector.o
	$(CXX) -o $@ $^

main.o: main.cc ann.h minimization.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

ann.o: ann.cc ann.h minimization.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

minimization.o: minimization.cc minimization.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

QR.o: QR.cc QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

matrix.o: matrix.cc matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.txt main *.o *.svg