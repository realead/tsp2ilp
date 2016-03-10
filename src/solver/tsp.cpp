#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <limits>


#include "TSPGraph.h"

//returns the cost of the minimal hamilton cycle or infinity otherwise
double minimize_tsp(const TSPGraph &graph){
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
    TSPGraph graph=readTSPGraph(std::cin);
    std::cout<<"minimum costs: "<<minimize_tsp(graph)<<std::endl;
}
