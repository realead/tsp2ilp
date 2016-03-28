import sys
import random
import math
sys.path.append('../src')
import tsp2ilp.graph as tspg

print sys.argv

output_file=sys.argv[1]
n=int(sys.argv[2])
seed=int(sys.argv[3])
random.seed(seed)

probability_edge=0.6

graph = tspg.TSPGraph()

for source in xrange(n):
    for target in xrange(n):  
        if (source!=target) and (random.uniform(0.0, 1.0)<probability_edge):
            graph.add_edge(source, target, random.randint(0,100))
            #graph.add_edge(source, target, 1)
            
graph.save_to_file(output_file)

