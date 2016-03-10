#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <limits>


 struct Edge{
    size_t goal;
    double weight;
    Edge(size_t goal_, double weight_):goal(goal_), weight(weight_){}
};
    
    
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
    typedef std::pair<size_t, size_t> Configuration;//first - last node, second - visited set
    typedef std::map<Configuration, double> Map;
    Map costs;
    costs[std::make_pair(0, 1)]=0.0;//start in the 0;
    
    //brute force:
    for (size_t i=1;i<graph.nodeCnt();i++){
        Map next;
        
        for( auto cur : costs){
           size_t last=cur.first.first;
           size_t set=cur.first.second;
           double cost=cur.second;
           
           for( auto edge : graph.getNeighbors(last)){
                size_t mask=1<<edge.goal;
                
                if( !(mask&set)){
                    Configuration con(edge.goal, mask|set);
                    double newCost=cost+edge.weight;
                    auto curCost=next.find(con);
                    if(curCost==next.end())
                        next.insert(std::make_pair(con, newCost));
                    else
                        curCost->second=std::min(newCost, curCost->second);
                }
           }
        }
        costs=next;
    }
    
    double res=std::numeric_limits<double>::infinity();
    
    for( auto cur : costs){
       size_t last=cur.first.first;
       double cost=cur.second;
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
