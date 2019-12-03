#Define Compiler:
CC=g++ -std=c++11
CFLAGS = -c
LFLAGS = -o
OFLAGS = -O2
#Define the processes:
all: compile_all

compile_all: Top-K_Naive Top-K_LB Top-K_Split Top-K_Index


Top-K_Naive: Top-K_Naive.o
	$(CC) $(LFLAGS) Top-K_Naive Top-K_Naive.o

Top-K_Naive.o: Top-K_Naive.cpp
	$(CC) $(CFLAGS) $(OFLAGS) Top-K_Naive.cpp

Top-K_LB: Top-K_LB.o
	$(CC) $(LFLAGS) Top-K_LB Top-K_LB.o 

Top-K_LB.o: Top-K_LB.cpp 
	$(CC) $(CFLAGS) $(OFLAGS) Top-K_LB.cpp

Top-K_Split: Top-K_Split.o
	$(CC) $(LFLAGS) Top-K_Split Top-K_Split.o 

Top-K_Split.o: Top-K_Split.cpp 
	$(CC) $(CFLAGS) $(OFLAGS) Top-K_Split.cpp

Top-K_Index: Top-K_index.o
	$(CC) $(LFLAGS) Top-K_Index Top-K_index.o 

Top-K_index.o: Top-K_index.cpp 
	$(CC) $(CFLAGS) $(OFLAGS) Top-K_index.cpp

clean:
	rm *.o
	rm Top-K_Naive
	rm Top-K_Index
	rm Top-K_Split
	rm Top-K_LB
