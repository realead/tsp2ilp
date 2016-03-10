

python create2dcase.py temp.tsp 20
python from2DtoGraph.py temp.tsp temp.graph

echo "java:"
time java -cp ../bin TSP < temp.tsp


echo "\n\n\n\nbrute force hash:"
time ../bin/tsp < temp.graph

echo "\n\n\n\nbrute force:"
time ../bin/tsp_opt < temp.graph

python ../src/tsp2ilp/tsp2ilp.py temp.graph temp.lp > log.txt

echo "\n\nilp:\n\n"
time ../bin/lp_solve temp.lp | grep "Value of objective"

echo "\n\n\n"
