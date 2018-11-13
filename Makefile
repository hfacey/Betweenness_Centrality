CC = g++
CFLAGS = -Wall -g -std=c++11 -fopenmp
OPENMP = -fopenmp

TARGETS = benchmark-dijkstra benchmark-bfs

all: $(TARGETS)

benchmark-dijkstra: benchmark-dijkstra.cc BC.o readGraph.o BinHeap.o shortestPaths.o
	$(CC) $(CFLAGS) -o $@ benchmark-dijkstra.cc BC.o readGraph.o BinHeap.o shortestPaths.o

benchmark-bfs: benchmark-bfs.cc BC.o readGraph.o BinHeap.o shortestPaths.o
	$(CC) $(CFLAGS) -o $@ benchmark-bfs.cc BC.o readGraph.o BinHeap.o shortestPaths.o

BC.o: BC.h BC.cc
	$(CC) $(CFLAGS) -c BC.cc

readGraph.o: readGraph.h readGraph.cc
	$(CC) $(CFLAGS) -c readGraph.cc

shortestPaths.o: shortestPaths.h shortestPaths.cc
	$(CC) $(CFLAGS) -c shortestPaths.cc

BinHeap.o: BinHeap.h BinHeap.cc
	$(CC) $(CFLAGS) -c BinHeap.cc

clean:
	rm -f *.o $(TARGETS) *.stdout
