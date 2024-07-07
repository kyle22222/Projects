PROGRAM = test

CXX = g++

CXXFLAGS = -std=c++11

SOURCES = Escape.cc Hero.cc PartArray.cc Participant.cc Pit.cc Position.cc random.cc Snorc.cc
OBJECTS = $(SOURCES:.cc=.o)

HEADERS = defs.h Escape.h Hero.h PartArray.h Participant.h Pit.h Position.h Snorc.h

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o $(PROGRAM)
