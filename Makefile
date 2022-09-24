CC = g++         # Compiler Command
FLAGS = -Wall -g # Compiler Flags

# Object file names
OBJS = main.o

#Target for all
all: $(OBJS) 
	$(CC) $(FLAGS) -o MacroBoard $(OBJS)

main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp
