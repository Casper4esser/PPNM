CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: harmonic.svg damped.svg lotka_volterra.svg

harmonic.svg: harmonic.txt harmonic.gpi
	gnuplot harmonic.gpi

damped.svg: damped.txt damped.gpi
	gnuplot damped.gpi

lotka_volterra.svg: lotka_volterra.txt lotka_volterra.gpi
	gnuplot lotka_volterra.gpi

harmonic.txt damped.txt lotka_volterra.txt: main
	./$<

main: main.o ODE.o matrix.o vector.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc ODE.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

matrix.o: matrix.cc matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

ODE.o: ODE.cc ODE.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f main *.o *.svg *.txt
