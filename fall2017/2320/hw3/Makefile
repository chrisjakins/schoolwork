run: lab3fall17.driver.c RB.c RB.h
	gcc -Wall lab3fall17.driver.c RB.c
	./a.out < lab3fall17.a.dat

debug: lab3fall17.driver.c RB.c RB.h
	gcc -Wall lab3fall17.driver.c RB.c -g

test1: run
	./a.out < lab3fall17.a.dat > myoutput1
	diff myoutput1 lab3fall17.a.out

test2: run
	./a.out < lab3fall17.b.dat > myoutput2
	diff myoutput2 lab3fall17.b.out

testall: test1 test2

clean:
	-rm a.out myoutput*
