CXX ?= g++
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

.PHONY: clean

all: main_args main_cin main_file

main_args: main_args.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

main_cin: main_cin.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

main_file: main_file.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f main_args main_cin main_file out.txt input.txt