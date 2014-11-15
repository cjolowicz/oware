HEADERS = Position.hpp Engine.hpp Driver.hpp Debug.hpp
OBJECTS = main.o Position.o Engine.o Driver.o

CXXFLAGS += -Wall

all: oware

main.o: main.cpp $(HEADERS)

Position.o: Position.cpp $(HEADERS)

Engine.o: Engine.cpp $(HEADERS)

Driver.o: Driver.cpp $(HEADERS)

oware: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) oware
