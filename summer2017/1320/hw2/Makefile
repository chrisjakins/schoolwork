DEBUG = -g -Wall -Wshadow

prog: jakins-hw02.c
	c89 jakins-hw02.c -o prog

debug: jakins-hw02.c
	c89 $(DEBUG) jakins-hw02.c -o prog

test: prog
	-./prog > myoutput
	-./brezeale-hw02 > correct
	diff correct myoutput

clean:
	/bin/rm prog correct myoutput
