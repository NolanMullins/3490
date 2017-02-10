OBJQ1 = main.o
OBJQ2 = q2.o
FLAGS =-Wall -Iinclude -std=c99 
EXE1 = q1
EXE2 = q2

# -pthread

q2: $(OBJQ2) 
	gcc $(OBJQ2) -o q2 $(FLAGS)

q1: $(OBJQ1) 
	gcc $(OBJQ1) -o $(EXE1) $(FLAGS)

clean:
	rm $(OBJQ1) $(OBJQ2) $(EXE1) $(EXE2)

run:
	./$(EXE)

#%.o: src/$*.c
#	gcc -c src/$*.c $(FLAGS) -o $*.o
q2.o : src/q2.c
	gcc -c src/$*.c $(FLAGS) -o $*.o
main.o : src/main.c
	gcc -c src/$*.c $(FLAGS) -o $*.o