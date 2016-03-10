
import random
random.seed(20)


def save_graph(graph, file_name):
    lines=[]
    for i,edges in enumerate(graph):
        for edge in edges:
            lines.append("{0} {1[0]} {1[1]}\n".format(i, edge))
        
    with open(file_name, 'w') as f:
        f.writelines(lines)

for test_case_id in xrange(0,5):
    n=random.randint(5,20)
    graph=[list() for _ in xrange(0,n)]
    
    for source in xrange(0,n):
        edge_cnt=random.randint(n/2,n-1)
        for i in xrange(edge_cnt):
            target=random.randint(0,n-1)
            cost=random.randint(1,1000)
            graph[source].append((target, cost))
            
            
    save_graph(graph,"small_test_cases/test_%d.txt"%test_case_id)
    
    
