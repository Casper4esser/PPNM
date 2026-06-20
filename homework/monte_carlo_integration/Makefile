CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror -O3

.PHONY: all clean

all: out.txt mc_convergence.svg

mc_convergence.svg: mc_error.txt mc_convergence.gpi
	gnuplot mc_convergence.gpi

out.txt mc_error.txt: main
	./$< > out.txt

main: main.o mc.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc mc.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

mc.o: mc.cc mc.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *.txt main *.o *.svg