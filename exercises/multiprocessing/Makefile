CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror -O3 -pthread
N = 100000000

TIME = \time --format "$$nthreads %e %U" --append --output $@

.PHONY: all clean

all: time_plot.svg

main: main.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

out.times: main
	> $@
	> log.main
	for nthreads in 1 2 3 4 5 6 7 8; do \
		$(TIME) ./$< -threads $$nthreads -terms $(N) >> log.main; \
	done

time_plot.svg: out.times time_plot.gpi
	gnuplot time_plot.gpi

clean:
	rm -f main out.times log.main time_plot.svg