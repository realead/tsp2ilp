def save_graph(graph, file_name):
    lines=[]
    for i,edges in enumerate(graph):
        for edge in edges:
            lines.append("{0} {1[0]} {1[1]}\n".format(i, edge))
        
    with open(file_name, 'w') as f:
        f.writelines(lines)

import sys
import math

input_file=sys.argv[1]
output_file=sys.argv[2]

points2d=[]
with open(input_file,'r') as f:
    for line in f:
        line=line.strip()
        try:
            print line
            points2d.append(map(int, line.split()))
        except Exception as e:
            print e
            pass
        
n=len(points2d)
print "There are {0} points".format(n)

print points2d

graph=[list() for _ in xrange(0,n)]

for i in xrange(0,n):
  for j in xrange(i+1,n):
     p1=points2d[i]
     p2=points2d[j]
     dx=p1[1]-p2[1]
     dy=p1[2]-p2[2]
     d=int(round(math.sqrt(dx*dx+dy*dy)))
     graph[i].append((j,d))
     graph[j].append((i,d))
     
save_graph(graph, output_file)


