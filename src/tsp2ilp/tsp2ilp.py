#expects a directed graph as edges in format
#
# start_node1 end_node1 weight1
# start_node2 end_node2 weight2
# ...
#
#with start_node, end_node and weight expected to be interger
#
#


import graph as tspg
from ilpproblem import ILConstrain, ILProblem 

def graph2ilp(tspGraph):

    #number of cities:
    n=len(tspGraph)


    #sort incomming, outgoing edges:
    #constrains for nodes: incomming/outgoing edges are used once
    incomming=[ILConstrain(ILConstrain.EQUAL, result=1, name="in_%d"%i) for i in xrange(0,n)]
    outgoing=[ILConstrain(ILConstrain.EQUAL, result=1, name="out_%d"%i) for i in xrange(0,n)]
    e_names=[]

    #constrains for edges: trick which forces that there is exactly one cycle possible
    trick=[]
    u_names=set()

    cost_fun={}


    for i,edge in enumerate(tspGraph.get_all_edges()):
        edge_var="e"+str(i)
        e_names.append(edge_var)
        start_id=edge.start
        end_id=edge.goal
        
        #add to cost function:
        cost_fun[edge_var]=edge[2];
        
        #add info to node constrains:
        outgoing[edge.start].add_coeff(edge_var, 1)
        incomming[edge.goal].add_coeff(edge_var, 1)
        
        #add an edge constrain:
        if start_id and end_id:
            constrain=ILConstrain(ILConstrain.LESS_EQUAL, result=n-1, name="t_%d"%i)
            u_start="u"+str(edge.start)
            u_end="u"+str(edge.goal)
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
    
    
    return problem
    

def transform_graph2ilp(file_name_graph, file_name_ilp):
    tspGraph=tspg.read_TSPGraph(input_file)
    problem=graph2ilp(tspGraph) 
    with open(output_file,'w') as f:
        f.writelines(problem.export())  
        



if __name__=="__main__":            
    import sys
    input_file=sys.argv[1]
    output_file=sys.argv[2]

    transform_graph2ilp(input_file, output_file)


    
