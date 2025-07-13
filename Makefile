CC = gcc
CFLAGS = -Iinclude -g3 -Wall -Wextra -Werror -pedantic
PROGRAM = test

SRC_DIR = src
OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/pqueue.o $(SRC_DIR)/state.o $(SRC_DIR)/vector.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)
