GCC = c89 -Wall

run: jakins_hw2.c
	c89 jakins_hw2.c
	./a.out < lab2fall17.a.dat

debug: jakins_hw2.c
	c89 jakins_hw2.c -g

test1: run
	./a.out < lab2fall17.a.dat > myoutput1
	diff myoutput1 lab2fall17.a.out

test2: run
	./a.out < lab2fall17.b.dat > myoutput2
	diff myoutput2 lab2fall17.b.out

test3: run
	./a.out < lab2fall17.c.dat > myoutput3
	diff myoutput3 lab2fall17.c.out

testall: test1 test2 test3

clean:
	-rm a.out myoutput*
