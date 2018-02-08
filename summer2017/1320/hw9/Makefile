# based on http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
# Sat Apr 14 11:01:20 CDT 2012

CC=gcc 
SRC=hw09.c
BINLIB=hw09-lib.c
DEPS=hw09-lib.h

# type 
#   make
# to build
a.out: ${SRC} ${BINLIB} ${DEPS}
	${CC} -std=c89 -pedantic ${SRC} ${BINLIB}


# type 
#   make clean
# to remove a.out
clean:
	rm a.out
