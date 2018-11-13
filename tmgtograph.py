import sys
import math

if len(sys.argv) < 3:
    print("Too few arguments. Usage: python3 roadmap.py <input tmg file> <output file>")
    exit(1)
    
fin = open(sys.argv[1])
fout = open(sys.argv[2], 'w')

#Skip the first line
fin.readline()

#Get/print the number of vertices and edges
l = fin.readline()
numV = int(l.split()[0])
numE = int(l.split()[1])
fout.write(str(numV) + " " + str(2*numE) + "\n")

names = []
coords = {}

#Get/print the vertices
for i in range(numV):
    l = fin.readline()
    names.append(l.split()[0])
    fout.write(names[-1] + "\n")
    
    long = float(l.split()[1])
    lat = float(l.split()[2])
    coords[names[-1]] = (math.radians(long), math.radians(lat))

#Get the edges
edges = []
for i in range(numE):
    l = fin.readline()
    edge = l.split()
    edge[0] = int(edge[0])
    edge[1] = int(edge[1])
    edges.append(edge)

    reverseEdge = edge[:]
    reverseEdge[0], reverseEdge[1] = reverseEdge[1], reverseEdge[0]
    edges.append(reverseEdge)

#Sort the edges
edges.sort()
    

#Print the edges    
for e in edges:
    src = e[0]
    dest = e[1]
    label = e[2]
    
    #Compute Haversine distance
    dlong = coords[names[dest]][0] - coords[names[src]][0]
    dlat = coords[names[dest]][1] - coords[names[src]][1]
    a = math.sin(dlat/2)**2 + math.cos(coords[names[src]][1]) * math.cos(coords[names[dest]][1]) * math.sin(dlong/2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    dist = c*3963.19 #miles

    fout.write(str(src) + " " + str(dest) + " " + str(dist) + " " + label + "\n")

