GCC = c89 -Wall

run: jakins_hw1.c
	c89 jakins_hw1.c
	
test1: run
	./a.out < lab1fall17.a.dat > myoutput1
	diff myoutput1 lab1fall17.a.out

test2: run
	./a.out < lab1fall17.b.dat > myoutput2
	diff myoutput2 lab1fall17.b.out

test3: run
	./a.out < lab1fall17.c.dat > myoutput3
	diff myoutput3 lab1fall17.c.out

testall: test1 test2 test3

clean:
	- rm a.out myoutput*
