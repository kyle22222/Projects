# Executable name
PROGRAM = program

# Compiler
CXX = g++

# Source files and their corresponding object files
SOURCES = Control.cc Course.cc CourseArray.cc Registration.cc RegList.cc School.cc StuArray.cc Student.cc View.cc
OBJECTS = $(SOURCES:.cc=.o)

# Header files
HEADERS = Control.h Course.h CourseArray.h Registration.h RegList.h School.h StuArray.h Student.h View.h defs.h

# Default target
$(PROGRAM): $(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) -std=c++11

# Pattern rule for object files
%.o: %.cc $(HEADERS)
	$(CXX) -c $< -std=c++11

# Phony target for clean
.PHONY: clean

clean:
	rm -f *.o $(PROGRAM)
