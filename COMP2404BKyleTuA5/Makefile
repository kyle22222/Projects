PROGRAM = test

CXX = g++

CXXFLAGS = -std=c++11 -Wall

# Add all source files involved in the project
SOURCES = Escape.cc Hero.cc Participant.cc Snorc.cc Ninja.cc random.cc
OBJECTS = $(SOURCES:.cc=.o)

# Include all header files involved in the project, now including List.h
HEADERS = defs.h Escape.h Hero.h Participant.h Snorc.h Ninja.h \
          MoveBehaviour.h EscapeeBehaviour.h RescuerBehaviour.h \
          VillainBehaviour.h RescuedBehaviour.h List.h random.h

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)

%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o $(PROGRAM)
