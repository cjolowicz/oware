HEADERS = Board.hpp Position.hpp Engine.hpp Driver.hpp Debug.hpp \
	  Singleton.hpp Exception.hpp Assert.hpp String.hpp
OBJECTS = Board.o Position.o Engine.o Driver.o Exception.o String.o
EXTRA_OBJECTS = main.o

TEST_HEADERS = TestCase.hpp TestSuite.hpp TestRunner.hpp Test.hpp
TEST_OBJECTS = TestCase.o TestSuite.o TestRunner.o
TESTS = TestString TestPosition TestEngine
EXTRA_TEST_OBJECTS = TestPosition.o TestEngine.o TestString.o

CXXFLAGS += -Wall

all: oware $(TESTS)

main.o: main.cpp $(HEADERS)

Board.o: Board.cpp $(HEADERS)

Position.o: Position.cpp $(HEADERS)

Engine.o: Engine.cpp $(HEADERS)

Driver.o: Driver.cpp $(HEADERS)

Exception.o: Exception.cpp $(HEADERS)

String.o: String.cpp $(HEADERS)

TestCase.o: TestCase.cpp $(TEST_HEADERS) $(HEADERS)

TestSuite.o: TestSuite.cpp $(TEST_HEADERS) $(HEADERS)

TestRunner.o: TestRunner.cpp $(TEST_HEADERS) $(HEADERS)

oware: main.o $(OBJECTS)
	$(CXX) -o $@ main.o $(OBJECTS)

TestString.o: TestString.cpp $(TEST_HEADERS) $(HEADERS)

TestString: TestString.o $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) -o $@ TestString.o $(TEST_OBJECTS) $(OBJECTS)

TestPosition.o: TestPosition.cpp $(TEST_HEADERS) $(HEADERS)

TestPosition: TestPosition.o $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) -o $@ TestPosition.o $(TEST_OBJECTS) $(OBJECTS)

TestEngine.o: TestEngine.cpp $(TEST_HEADERS) $(HEADERS)

TestEngine: TestEngine.o $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) -o $@ TestEngine.o $(TEST_OBJECTS) $(OBJECTS)

run: oware
	./oware <<<B

test: $(TESTS)
	@for test in $(TESTS) ; do \
	  ./$$test; \
	done

clean:
	rm -f oware $(OBJECTS) $(TEST_OBJECTS) $(TESTS) $(EXTRA_OBJECTS) $(EXTRA_TEST_OBJECTS)
