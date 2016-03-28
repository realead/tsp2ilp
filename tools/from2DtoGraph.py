import sys
import math

sys.path.append('../src')
import tsp2ilp.graph as tspg


input_file=sys.argv[1]
output_file=sys.argv[2]

points2d=[]
with open(input_file,'r') as f:
    for line in f:
        line=line.strip()
        try:
            #print line
            points2d.append(map(int, line.split()))
        except Exception as e:
            #print e
            pass
        
n=len(points2d)
print "There are {0} points".format(n)

points=[point[1:] for point in points2d]

#print points

graph=tspg.create_TSPGraph_from_2dpoints(points)
graph.save_to_file(output_file)


