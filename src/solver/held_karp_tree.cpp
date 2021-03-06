#include <iostream>
#include <map>

#include "TSPGraph.h"
#include "HeldKarpTSPSolver.h"

/* uses held-karp algorithm swhich uses std::set for memoization */

int main(){
    TSPGraph graph=readTSPGraph(std::cin);
    std::cout<<"minimum costs: "<<held_karp_sets<std::map>(graph)<<std::endl;
}


