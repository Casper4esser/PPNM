CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

GENERATED_TXT_FILES = erf_data.txt gamma_data.txt lngamma_data.txt \
					  gamma_points.txt lngamma_points.txt cgamma_data.txt

.PHONY: all clean

all: erf_fig.svg gamma_fig.svg lngamma_fig.svg cgamma_fig.svg

erf_fig.svg: erf_data.txt erf_fig.gpi
	gnuplot erf_fig.gpi

gamma_fig.svg: gamma_data.txt gamma_fig.gpi
	gnuplot gamma_fig.gpi

lngamma_fig.svg: lngamma_data.txt lngamma_fig.gpi
	gnuplot lngamma_fig.gpi

cgamma_fig.svg: cgamma_data.txt cgamma_fig.gpi
	gnuplot cgamma_fig.gpi

$(GENERATED_TXT_FILES): main
	./main

main: main.o funs.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc funs.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

funs.o: funs.cc funs.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f *_fig.svg main *.o $(GENERATED_TXT_FILES)