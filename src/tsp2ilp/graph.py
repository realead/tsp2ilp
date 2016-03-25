import sys
import math
import itertools
from collections import namedtuple

#a python version of TSPGraph: just a list of edges
class TSPGraph:

    def __init__(self):
        self.nodeMap={}
        self.graph=[]
        
        
        
    def get_id(self, node):
        if not node in self.nodeMap:
            self.nodeMap[node]=len(self.nodeMap)
        return self.nodeMap[node]
    
    
    
    def get_all_edges(self):
        return iter(self.graph)
    
  
    
        
    def add_edge(self, start, goal, weight):
        Edge = namedtuple('Edge', 'start goal weight')
        indexStart=self.get_id(start)
        indexGoal=self.get_id(goal)
        self.graph.append(Edge(indexStart, indexGoal, weight))
    
    
    
    
    def save_to_file(self, file_name):
        inv_map = {v: k for k, v in self.nodeMap.items()}
        lines=[]
        for edge in self.get_all_edges():
            lines.append("{0} {1} {2}\n".format(inv_map[edge.start], inv_map[edge.goal], edge.weight))
        
        with open(file_name, 'w') as f:
            f.writelines(lines)
       
       
             
    def print_out(self):
       for edge in self.get_all_edges():
           sys.stdout.write("%d->%d(%f)\n"%(edge.start, edge.goal, edge.weight))

       sys.stdout.write('\n')
        
        
        
        
        
        
#a line of TSPGraph is an edge in the form 
#  "start1 goal1 cost1"
#  "start2 goal2 cost2"
# with startX, goalX any names and costX a float value

def read_TSPGraph(file_name):
    result=TSPGraph()
    #parsing input:
    with open(file_name, 'r') as f:
        for line in f:
            edge=line.strip().split()
            result.add_edge(edge[0], edge[1], float(edge[2]))
            
    return result
            

#creates a complete graph with costs of the edges equal to the
def create_TSPGraph_from_2dpoints(points):
    graph=TSPGraph()
    n = len(points)
    for i in xrange(0,n):
        for j in xrange(i+1,n):
            p1=points[i]
            p2=points[j]
            dx=p1[0]-p2[0]
            dy=p1[1]-p2[1]
            d=int(round(math.hypot(dx, dy)))
            graph.add_edge(i,j,d)
            graph.add_edge(j,i,d)
            
    return graph
            

if __name__=="__main__":

    graph=TSPGraph()
    graph.add_edge("A", "B", 1)
    graph.add_edge("A", "C", 2)
    graph.add_edge("C", "B", 3)
    graph.add_edge("B", "C", 4)
    
    graph.print_out()
    
    print list(graph.get_all_edges())
    
    graph.save_to_file("temp.graph")
    
    graph=read_TSPGraph("temp.graph")
    graph.print_out()
    
    graph=create_TSPGraph_from_2dpoints([(0,3),(1,0)])
    graph.print_out()
    
