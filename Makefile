HEADERS = Position.hpp Engine.hpp Driver.hpp Debug.hpp Singleton.hpp \
	  Exception.hpp
OBJECTS = Position.o Engine.o Driver.o Exception.o

TEST_HEADERS = TestCase.hpp TestSuite.hpp
TEST_OBJECTS = TestCase.o TestSuite.o
TESTS = TestPosition

CXXFLAGS += -Wall

all: oware $(TESTS)

main.o: main.cpp $(HEADERS)

Position.o: Position.cpp $(HEADERS)

Engine.o: Engine.cpp $(HEADERS)

Driver.o: Driver.cpp $(HEADERS)

Exception.o: Exception.cpp $(HEADERS)

TestCase.o: TestCase.cpp $(TEST_HEADERS) $(HEADERS)

TestSuite.o: TestSuite.cpp $(TEST_HEADERS) $(HEADERS)

oware: main.o $(OBJECTS)
	$(CXX) -o $@ main.o $(OBJECTS)

TestPosition.o: TestPosition.cpp $(TEST_HEADERS) $(HEADERS)

TestPosition: TestPosition.o $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) -o $@ TestPosition.o $(TEST_OBJECTS) $(OBJECTS)

clean:
	rm -f oware $(OBJECTS) $(TEST_OBJECTS) $(TESTS)
