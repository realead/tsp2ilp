#pragma once

#include <set>
#include <utility>
#include <limits>
#include <type_traits>

#include "TSPGraph.h"

//needed inside of held_karp, we are not using std::pair
//because we can speziaize a std-template only if a template parameter is user defined
//needed for std::hash

struct Configuration{
  size_t last;
  size_t set;
  Configuration(size_t l, size_t s):last(l), set(s){}
};

inline bool operator<(const Configuration &lhs, const Configuration &rhs){
  if(lhs.last==rhs.last)
     return lhs.set<rhs.set;
  return lhs.last<rhs.last;
}

inline bool operator==(const Configuration &lhs, const Configuration &rhs){
  return lhs.last==rhs.last &&  lhs.set==rhs.set;
}

namespace std{
template<>
struct hash<Configuration>{
    size_t operator()(const Configuration & x) const
    {
      //FIXME: a better hash function!
      return (x.last*311+x.set)%3036581853143L;
    }
  };
}


/* 

   implements Held-Karp-Algorithm and uses sets (std::set or std::unordered_set) for memoization 


   returns the cost of the minimal hamilton cycle or infinity, if no hamilton cycle possible
*/


template<template<typename ... >  class MemType>
inline double held_karp_sets(const TSPGraph &graph){
    typedef MemType<Configuration, double> Map;
    Map costs;
    costs[Configuration(0, 1)]=0.0;//start in the 0;
    
    //find best hamiltonian paths from 0 to any other node:
    for (size_t i=1;i<graph.nodeCnt();i++){
        Map next;
        
        for( auto cur : costs){
           size_t last=cur.first.last;
           size_t set=cur.first.set;
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
    
    //find the last edge back to 0, choose the best
    double res=std::numeric_limits<double>::infinity();
    
    for( auto cur : costs){
       size_t last=cur.first.last;
       double cost=cur.second;
       for( auto edge : graph.getNeighbors(last))
            if(edge.goal==0)
                  res=std::min(cost+edge.weight, res);
    } 
    
    return res;   
}


