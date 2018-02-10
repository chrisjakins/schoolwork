GCC = g++ -std=c++11 -pedantic

main: main.cpp student.cpp
	$(GCC) main.cpp
	./a.out

test: test_student.cpp student.cpp
	$(GCC) test_student.cpp
	./a.out

clean:
	-/bin/rm -f *.0 a.out
