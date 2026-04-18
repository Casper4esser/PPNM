CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: all clean

all: out.txt

out.txt: main
	./$< > $@

# Normalt bruges CXXFLAGS kun ved kompileringen men ved avancerede ting, 
# som man måske en dag skal lave i fremtiden, kræves der åbenbart også flags her.
# Derudover har jeg skiftet til C++ compiler i stedet for C compiler med C++ ting tilføjet.
main: main.o approx.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cc approx.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

approx.o: approx.cc approx.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f out.txt main




