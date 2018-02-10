CFLAGS := -std=c++11 -pedantic -Wall
OBJECTS := main.o publication.o library.o

run: $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS)
	./a.out

testpub: publication.o test-publication.o
	$(CXX) $(CFLAGS) $?
	./a.out

testlib: library.o publication.o test-library.o
	$(CXX) $(CFLAGS) $?
	./a.out 

main.o: main.cpp
	$(CXX) $(CFLAGS) -c $?

publication.o: publication.cpp publication.h
	$(CXX) $(CFLAGS) -c publication.cpp

library.o: library.cpp library.h
	$(CXX) $(CFLAGS) -c library.cpp

test-library.o: test-library.cpp
	$(CXX) $(CFLAGS) -c $?

test-publication.o: test-publication.cpp
	$(CXX) $(CFLAGS) -c $?

clean:
	-rm *.o a.out
