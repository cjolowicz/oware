HEADERS = Position.hpp
OBJECTS = main.o Position.o

all: oware

main.o: main.cpp $(HEADERS)

Position.o: Position.cpp $(HEADERS)

oware: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) oware
