
#build cpp solver:
g++ -std=c++11 -O3 ../src/solver/held_karp_tree.cpp -o ../bin/held_karp_tree
g++ -std=c++11 -O3 ../src/solver/tsp_opt.cpp -o ../bin/tsp_opt

#javac -d ../bin ../src/solver/TSP.java 


