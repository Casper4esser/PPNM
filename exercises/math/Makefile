# kommentarerne er for min egen læring og ikke til nogen, som læser koden. 

# ?= er soft assignment. Dvs. hvis computeren allerede har en compiler, så bruges den i stedet for g++.
CXX ?= g++
CC ?= gcc

# += sørger for at CXXFLAGS listen udvides og ikke overskrides.
CXXFLAGS += -std=c++20 -Wall -Wextra -Werror

# lstdc++ er biblioteket med alle C++ funktioner. Vi bruger nemlig en C-compiler til at linke object codes.
# -lm står for link math. Den sørger somehow for, at man kan regne?
LDLIBS += -lstdc++ -lm

# siger at all og clean ikke er filer, så der ikke opstår forvirring, 
# hvis der nogensinde skulle blive lavet filer, som hedder all eller clean
.PHONY: all clean 

all: Out.txt

# $@ er automatic variable for target
# $< er automatic variable for prerequisite
Out.txt : math
	./$< > $@

# $^ er automatic variable for alle prerequisites
math: math.o sfuns.o
	$(CC) -o $@ $^ $(LDLIBS)	

math.o: math.cc sfuns.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

sfuns.o: sfuns.cc sfuns.h
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f Out.txt math *.o