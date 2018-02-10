CFLAGS := -std=c++11 -pedantic -Wall
OBJECTS := main.o publication.o library.o patron.o dialogs.o
GTK := `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

run: $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) $(GTK)
	./a.out

testpub: publication.o test-publication.o patron.o
	$(CXX) $(CFLAGS) $?
	./a.out

testlib: library.o publication.o test-library.o patron.o
	$(CXX) $(CFLAGS) $?
	./a.out 

main.o: main.cpp
	$(CXX) $(CFLAGS) $(GTK) -c $?

publication.o: publication.cpp publication.h
	$(CXX) $(CFLAGS) -c publication.cpp

library.o: library.cpp library.h
	$(CXX) $(CFLAGS) -c library.cpp

patron.o: patron.cpp patron.h
	$(CXX) $(CFLAGS) -c patron.cpp

dialogs.o: dialogs.cpp dialogs.h
	$(CXX) $(CFLAGS) $(GTK) -c dialogs.cpp

test-library.o: test-library.cpp
	$(CXX) $(CFLAGS) -c $?

test-publication.o: test-publication.cpp
	$(CXX) $(CFLAGS) -c $?

clean:
	-rm *.o a.out
