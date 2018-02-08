DEBUG = -g -Wall -Wshadow
VALG = valgrind --tool=memcheck --leak-check=full --verbose --log-file=

prog: jakins-hw03.c
	c89 jakins-hw03.c -o prog

debug: jakins-hw02.c
	c89 $(DEBUG) jakins-hw03.c -o prog

testall: test1 test2 test3 test4 test5 test6

test1: prog
	-./prog 1 20 > myoutput1
	-./brezeale-hw03 1 20 > correct1
	diff correct1 myoutput1
	#$(VALG)log1 ./prog 1 20

test2: prog
	-./prog 10 30 > myoutput3
	-./brezeale-hw03 10 30 > correct3
	diff correct3 myoutput3
	#$(VALG)log2 ./prog 10 30

test3: prog
	-./prog 1 100 > myoutput3
	-./brezeale-hw03 1 100 > correct3
	diff correct3 myoutput3
	#$(VALG)log3 ./prog 1 100

test4: prog
	-./prog 0 20 > myoutput4
	-./brezeale-hw03 0 20 > correct4
	diff correct4 myoutput4
	#$(VALG)log4 ./prog 0 20

test5: prog
	-./prog 99 101 > myoutput5
	-./brezeale-hw03 99 101 > correct5
	diff correct5 myoutput5
	#$(VALG)log5 ./prog 99 101

test6: prog
	-./prog 20 5 > myoutput
	-./brezeale-hw03 20 5 > correct
	diff correct myoutput
	#$(VALG)log6 ./prog 20 5

clean:
	/bin/rm prog myoutput* correct* log*
