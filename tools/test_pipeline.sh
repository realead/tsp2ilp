

python create2dcase.py temp.tsp 18 20
python from2DtoGraph.py temp.tsp temp.graph

#echo "java:"
#time java -cp ../bin TSP < temp.tsp


#brute force approaches:
echo "\n\n\n\nbrute force tree:"
time ../bin/held_karp_tree < temp.graph

echo "\n\n\n\nbrute force hash:"
time ../bin/held_karp_hash < temp.graph

echo "\n\n\n\nbrute force:"
time ../bin/tsp_opt < temp.graph



#solving using lp_solve
python ../src/tsp2ilp/tsp2ilp.py --LP temp.graph temp.lp 
echo "\n\lp_solve:\n\n"
time ../bin/lp_solve temp.lp | grep "Value of objective"



#solving using scip and nglsol:
python ../src/tsp2ilp/tsp2ilp.py --IBMLP temp.graph temp_ibm.lp 

echo "\n\nscip:\n\n"
time ../bin/scip -f temp_ibm.lp | grep "objective value"

echo "\n\nglpsol:\n\n"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../third_party/glpk-4.59/lib
time ../bin/glpsol --lp temp_ibm.lp | grep "tree is empty"

echo "\n\n\n"
