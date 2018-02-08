DEBUG = -g -Wall -Wshadow 
VALG = valgrind --tool=memcheck --leak-check=full --verbose --log-file=

a.out: version3.c
	c89 version3.c

test: test.c a.out
	c89 test.c -o test
	./test

debug: version2.c
	c89 $(DEBUG) version3,c
	gdb a.out

valgtest: a.out
	$(VALG)log0 ./a.out < data-001.txt

clean:
	rm myoutput* correct* a.out test
