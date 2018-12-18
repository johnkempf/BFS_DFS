OBJS = da.o cda.o stack.o queue.o integer.o maze.o cell.o amaze.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : amaze

amaze : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o amaze

da.o : da.c da.h
		gcc $(OOPTS) da.c

cda.o : cda.c cda.h
		gcc $(OOPTS) cda.c

stack.o : stack.c stack.h
		gcc $(OOPTS) stack.c

queue.o : queue.c queue.h
		gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
		gcc $(OOPTS) integer.c

amaze.o : amaze.c integer.h 
		gcc $(OOPTS) amaze.c

cell.o : cell.c cell.h
		gcc $(OOPTS) cell.c

maze.o : maze.c maze.h
		gcc $(OOPTS) maze.c

test : amaze
		./amaze -c 3 3 m -s m p -d p

valgrind : amaze
		valgrind ./amaze

clean	:
		rm -f $(OBJS) amaze
		rm -f *.o
