#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <string>

/*

A simple graph representation as an adjacency list.

Nodes are identified by a string label

*/



struct Edge{
    size_t goal;
    double weight;
    Edge(size_t goal_, double weight_):goal(goal_), weight(weight_){}
};
    
    
class TSPGraph{

  public:
    //for graph initialization:   
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
   
    //topology access (nodes have size_t ids):
    const Neighbors &getNeighbors(size_t index) const{
        return graph[index];
    }
    
    size_t nodeCnt() const{
        return graph.size();
    }
    
    
    //for debug purposes:
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


/*
  reads a tsp graph written in the format:
  
  start_node_label0 end_node_label0 directed_edge_cost0
  start_node_label1 end_node_label1 directed_edge_cost1
  ....
  start_node_labelN end_node_labelN directed_edge_costN
  
  with exactly N+1 lines without any comments
*/
TSPGraph readTSPGraph(std::istream &input){
    TSPGraph graph;
    while(true){
       std::string from;
       std::string to;
       double w;
       input>>from>>to>>w;
       if(! input.good() || input.eof())
            break;
       graph.addEdge(from, to, w);
    }
    
    return graph; 
}
