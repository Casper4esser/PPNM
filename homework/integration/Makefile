CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt erf_convergence.svg

erf_convergence.svg: erf_convergence.txt erf_convergence.gpi
	gnuplot erf_convergence.gpi

out.txt erf_convergence.txt: main
	./$< > out.txt

main: main.o integrate.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc integrate.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

integrate.o: integrate.cc integrate.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.txt main *.o *.svg