run: kruskal.c 
	gcc -Wall kruskal.c -lm
	./a.out < lab4fall17.a.dat

debug: kruskal.c
	gcc -Wall kruskal.c -g -lm

test1: run
	./a.out < lab4fall17.a.dat > myoutput1
	diff myoutput1 lab4fall17.a.out

test2: run
	./a.out < lab4fall17.b.dat > myoutput2
	diff myoutput2 lab4fall17.b.out

test3: run
	./a.out < lab4fall17.c.dat > myoutput3
	diff myoutput3 lab4fall17.c.out

test4: run
	./a.out < lab4fall17.d.dat > myoutput4
	diff myoutput4 lab4fall17.d.out

testall: test1 test2 test3 test4

clean:
	-rm a.out myoutput*
