#expects a directed graph as edges in format
#
# start_node1 end_node1 weight1
# start_node2 end_node2 weight2
# ...
#
#with start_node, end_node and weight expected to be interger
#
#

import sys
input_file=sys.argv[1]
output_file=sys.argv[2]


#parsing input:
with open(input_file, 'r') as f:
    edges=f.readlines()

print "\n".join(edges)

edges=[map(int, edge.strip().split()) for edge in edges]

print "\n".join(map(str,edges))

#enumerate cities:
city2id={}
id2city=[]

for edge in edges:
    for city in edge[:-1]:
      if city not in city2id:
        city2id[city]=len(id2city)
        id2city.append(city)
        
print city2id
print id2city


#sort incomming, outgoing edges:
from ilpproblem import ILConstrain, ILProblem 

#number of cities:
n=len(id2city)

#constrains for nodes: incomming/outgoing edges are used once
incomming=[ILConstrain(ILConstrain.EQUAL, result=1, name="in_%d"%i) for i in xrange(0,n)]
outgoing=[ILConstrain(ILConstrain.EQUAL, result=1, name="out_%d"%i) for i in xrange(0,n)]
e_names=[]

#constrains for edges: trick which forces that there is exactly one cycle possible
trick=[]
u_names=set()

cost_fun={}


for i,edge in enumerate(edges):
    edge_var="e"+str(i)
    e_names.append(edge_var)
    start_id=city2id[edge[0]]
    end_id=city2id[edge[1]]
    
    #add to cost function:
    cost_fun[edge_var]=edge[2];
    
    #add info to node constrains:
    outgoing[start_id].add_coeff(edge_var, 1)
    incomming[end_id].add_coeff(edge_var, 1)
    
    #add an edge constrain:
    if start_id and end_id:
        constrain=ILConstrain(ILConstrain.LESS_EQUAL, result=n-1, name="t_%d"%i)
        u_start="u"+str(start_id)
        u_end="u"+str(end_id)
        constrain.add_coeff(u_start, 1)
        constrain.add_coeff(u_end, -1)
        constrain.add_coeff(edge_var, n)
        trick.append(constrain)
        u_names.add(u_start)
        u_names.add(u_end)
   

problem=ILProblem()

problem.set_cost_fun(cost_fun)
problem.append_constrains(incomming)
problem.append_constrains(outgoing)
problem.append_constrains(trick)

problem.define_as_int_vars(u_names)
problem.define_as_bin_vars(e_names)

print cost_fun
print "".join(problem.export())

with open(output_file,'w') as f:
    f.writelines(problem.export())
    
