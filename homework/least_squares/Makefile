CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

GENERATED_TXT_FILES = rutherford_data.txt rutherford_fit.txt

.PHONY: all clean

all: out.txt rutherford_fig.svg

rutherford_fig.svg: rutherford_data.txt rutherford_fit.txt rutherford_fig.gpi
	gnuplot rutherford_fig.gpi

out.txt: main
	./$< > $@

main: main.o lsfit.o QR.o matrix.o vector.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc lsfit.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

vector.o: vector.cc vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

matrix.o: matrix.cc matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

QR.o: QR.cc QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

lsfit.o: lsfit.cc lsfit.h QR.h matrix.h vector.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f out.txt main *.o *_fig.svg $(GENERATED_TXT_FILES)
