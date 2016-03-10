/*

a brute force approach (held karp) for TSP

uses 2d field for memoization

*/

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <cmath>

#include "TSPGraph.h"


size_t getNextSubset(size_t subset){
   size_t smallest = subset& -subset;       
   size_t ripple = subset + smallest;    
   size_t ones = subset ^ ripple;       
   ones = (ones >> 2)/smallest; 
   subset= ripple | ones;    
   return subset;
}


//returns the cost of the minimal hamilton cycle or infinity otherwise
double minimize_tsp(const TSPGraph &graph){
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
    TSPGraph graph=readTSPGraph(std::cin);
    std::cout<<"minimum costs: "<<minimize_tsp(graph)<<std::endl;
}
