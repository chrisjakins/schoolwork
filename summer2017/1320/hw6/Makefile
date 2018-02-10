DEBUG = -g -Wall -Wshadow
VALG = valgrind --tool=memcheck --leak-check=full --verbose --log-file=

a.out: jakins-hw06.c
	c89 jakins-hw06.c

debug: jakins-hw06.c
	c89 $(DEBUG) jakins-hw06.c

testall: test0 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 passed

test0: a.out
	-./a.out > myoutput0
	-./brezeale-hw06 > correct0
	diff correct0 myoutput0

test1: a.out
	-./a.out 1 20 > myoutput1
	-./brezeale-hw06 1 20 > correct1
	diff correct1 myoutput1
	#$(VALG)log1 ./a.out 1 20

test2: a.out
	-./a.out 10 40 > myoutput2
	-./brezeale-hw06 10 40 > correct2
	diff correct2 myoutput2
	#$(VALG)log2 ./a.out 10 30

test3: a.out
	-./a.out 1 100 > myoutput3
	-./brezeale-hw06 1 100 > correct3
	diff correct3 myoutput3
	#$(VALG)log3 ./a.out 1 100

test4: a.out
	-./a.out 0 20 > myoutput4
	-./brezeale-hw06 0 20 > correct4
	diff correct4 myoutput4
	#$(VALG)log4 ./a.out 0 20

test5: a.out
	-./a.out 99 101 > myoutput5
	-./brezeale-hw06 99 101 > correct5
	diff correct5 myoutput5
	#$(VALG)log5 ./a.out 99 101

test6: a.out
	-./a.out 20 5 > myoutput6
	-./brezeale-hw06 20 5 > correct6
	diff correct6 myoutput6
	#$(VALG)log6 ./a.out 20 5

test7: a.out
	-./a.out 5 5 > myoutput7
	-./brezeale-hw06 5 5 > correct7
	diff correct7 myoutput7
	#$(VALG)log7 ./a.out 5 5

test8: a.out
	-./a.out 73 73 > myoutput8
	-./brezeale-hw06 73 73 > correct8
	diff correct8 myoutput8
	#$(VALG)log8 ./a.out 73 73

test9: a.out
	-./a.out 60 > myoutput9
	-./brezeale-hw06 60 > correct9
	diff correct9 myoutput9
	#$(VALG)log9 ./a.out 60

test10: a.out
	-./a.out 60 61 62 > myoutput10
	-./brezeale-hw06 60 61 62> correct10
	diff correct10 myoutput10
	#$(VALG)log10 ./a.out 60 61 62

passed:
	echo "\n******* IF YOU GOT THIS FAR, CONGRATS! YOU'RE PROGRAM PASSED ALL TESTS *******\n"

clean:
	/bin/rm a.out myoutput* correct* log*
