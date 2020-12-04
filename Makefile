# lab-5/Makefile
# Ikechukwu Anude

sort: ParallelMergeSort.o
	gcc ParallelMergeSort.o -pthread -o sort

ParallelMergeSort.o: ParallelMergeSort.c
	gcc -c ParallelMergeSort.c

clean:
	*.o term