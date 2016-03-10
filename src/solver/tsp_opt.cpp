/*

a brute force approach (held karp) for TSP

uses 2d field for memoization

*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <limits>
#include <cmath>


 struct Edge{
    size_t goal;
    double weight;
    Edge(size_t goal_, double weight_):goal(goal_), weight(weight_){}
};
    
size_t getNextSubset(size_t subset){
   size_t smallest = subset& -subset;       
   size_t ripple = subset + smallest;    
   size_t ones = subset ^ ripple;       
   ones = (ones >> 2)/smallest; 
   subset= ripple | ones;    
   return subset;
}
	    
class Graph{
  public:   
    typedef std::vector<Edge> Neighbors;
    void addEdge(const std::string &from, const std::string &to, double weight){
       size_t f=getId(from);
       size_t t=getId(to);
       graph[f].push_back(Edge(t, weight));
    }
  private:
    typedef std::map<std::string, size_t> NodeMap;
    NodeMap nodes;
    std::vector<Neighbors> graph;
    
    size_t getId(const std::string &node){
        NodeMap::const_iterator it=nodes.find(node);
        if(it==nodes.end()){
            it=nodes.insert(std::make_pair(node, nodes.size())).first;
            graph.push_back(Neighbors());
        }
        return it->second;   
    }
   public:
    const Neighbors &getNeighbors(size_t index) const{
        return graph[index];
    }
    
    size_t nodeCnt() const{
        return graph.size();
    }
    
    
    void dump() const{
      std::cout<<nodeCnt()<<" nodes:\n";
      for(size_t i=0;i<nodeCnt();i++){
        std::cout<<i<<": ";
        for (auto edge : graph[i])
          std::cout<<"-->"<<edge.goal<<";";
        std::cout<<"\n";
      }
    }
    
};

//returns the cost of the minimal hamilton cycle or infinity otherwise
double minimize_tsp(const Graph &graph){
    size_t n=graph.nodeCnt();
    size_t MAX=1<<n;
    std::vector<std::vector<double> > mem(n, std::vector<double>(MAX, std::numeric_limits<double>::infinity()));
    mem[0][1]=0.0;
    
    //brute force:
    for (size_t i=1;i<graph.nodeCnt();i++){
        long long subset=(static_cast<size_t>(1)<<i)-1;
        while(subset<MAX){
            for(size_t last=0;last<n;last++)
                if(!std::isinf(mem[last][subset]))
                    for( auto edge : graph.getNeighbors(last)){
                        size_t mask=1<<edge.goal;
                        if( !(subset&mask)){
                            size_t next=subset|mask;
                            size_t next_goal=edge.goal;
                            double newCost=mem[last][subset]+edge.weight;
                            
                            mem[next_goal][next]=std::min(newCost, mem[next_goal][next]);
                        }
                    }
             subset=getNextSubset(subset);
        }
                
   }
    
    double res=std::numeric_limits<double>::infinity();
    
    for( size_t last=1;last<n;last++){
       double cost=mem[last][MAX-1];
       for( auto edge : graph.getNeighbors(last))
            if(edge.goal==0)
                  res=std::min(cost+edge.weight, res);
    } 
    
    return res;   
}


int main(){

//parse, read the graph:
    Graph graph;
    while(true){
       std::string from;
       std::string to;
       double w;
       std::cin>>from>>to>>w;
       if(! std::cin.good() || std::cin.eof())
            break;
       graph.addEdge(from, to, w);
    }
    std::cout<<"minimum costs: "<<minimize_tsp(graph)<<std::endl;
}
