CC = g++         # Compiler Command
FLAGS = -Wall -g # Compiler Flags

# Object file names
OBJS = main.o MacroHolder.o OutputHandler.o InputHandler.o MacroInterpreter.o

#Target for all
all: $(OBJS) 
	$(CC) $(FLAGS) -o MacroBoard $(OBJS)

main.o: src/main.cpp
	$(CC) $(FLAGS) -c src/main.cpp

MacroHolder.o: src/MacroHolder.cpp
	$(CC) $(FLAGS) -c src/MacroHolder.cpp

OutputHandler.o: src/OutputHandler.cpp
	$(CC) $(FLAGS) -c src/OutputHandler.cpp

InputHandler.o: src/InputHandler.cpp
	$(CC) $(FLAGS) -c src/InputHandler.cpp

MacroInterpreter.o: src/MacroInterpreter.cpp
	$(CC) $(FLAGS) -c src/MacroInterpreter.cpp

clean: 
	rm -f *.o 
