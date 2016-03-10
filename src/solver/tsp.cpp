#include <iostream>

#include "TSPGraph.h"
#include "HeldKarpTSPSolver.h"

/* uses held-karp algorithm swhich uses std::set for memoization */

int main(){
    TSPGraph graph=readTSPGraph(std::cin);
    std::cout<<"minimum costs: "<<held_karp_sets(graph)<<std::endl;
}


