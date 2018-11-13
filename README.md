# Betweenness_Centrality
Betweenness Centrality (BC) is a very well documented concept in graph theory, as it gives a measure of how critical a vertex is to a graph. A common way of calculating the BC is to first compute the “all pairs shortest path” for the graph. Then the more shortest paths a vertex appears in, the more “critical”/higher the BC it has.

This project evaluates the speedups possible with OpenMP by calculating the betweenness centrality of graphs in serial and parallel. The program can handle graphs with non-negative weights (in which case a version of Johnson's algorithm is used), or unweighted graphs (in which case Breadth-first-search is used).


Currently, the application is really set up to work with the Bridges supercomputer (or any system with 28 nodes to do the benchmark). Assuming you've loaded the file to Bridges (or equivalent system), you would run the following commands:

interact –ntasks-per-node=28

export OMP_NUM_THREADS=28

module load gcc/7.3.0

Then, you can just run "make". That generates 2 benchmark programs: benchmark-dijkstra and benchmark_bfs. They each take the output file as a command line paramenter. The programs will run with the graphs already provided.

If you don't have access to such a system, you can modify the benchmark-bfs.cc and benchmark-dijkstra.cc to run with the number of cores you have available.

This program was tested with graphs of road networks and flight/airport data. Some sample graphs are provided (named in the format <num_vertices>.txt). A good place to get data for road networks is http://tm.teresco.org/graphs/ (use the “simple” version of the graphs) which gives you a tmg file. You can feed the tmg file into the script tmgtograph.py to get a graph file in the correct format.
Run: python3 tmgtograph.py <tmg_file> <output_file>
