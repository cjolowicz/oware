HEADERS = Position.hpp Driver.hpp
OBJECTS = main.o Position.o Driver.o

all: oware

main.o: main.cpp $(HEADERS)

Position.o: Position.cpp $(HEADERS)

Driver.o: Driver.cpp $(HEADERS)

oware: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) oware
