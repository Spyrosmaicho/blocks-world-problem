CC = gcc
CFLAGS =  -g3 -Wall -Wextra -Werror -pedantic
PROGRAM = test
OBJS = main.o pqueue.o state.o vector.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)