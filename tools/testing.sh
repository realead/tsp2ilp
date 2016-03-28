#call sh testing.sh SOLVER POINT_CNT TEST_SET

# creates 10 different test cases with POINT_CNT vertices and let the solvers run for time_out time

solver=$1
pointCnt=$2
time_out="120s"
test_set=$3


echo "choosen solver: $solver" 
echo "choosen test_set: $test_set" 

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ed/mygithub/glpk-4.59/lib

for i in `seq 1 10`
do
    echo $i":\n"
    
    #create test case from test set:
    if [ "$test_set" = "2d" ]; then
        python create2dcase.py temp.tsp $pointCnt $i
        python from2DtoGraph.py temp.tsp temp.graph
    fi
    if [ "$test_set" = "random" ]; then
       python create_case.py temp.graph $pointCnt $i
    fi
    
    
    #solve the test case:
    if [ "$solver" = "lp_solve" ]; then
	    python ../src/tsp2ilp/tsp2ilp.py --LP temp.graph temp.lp 
        time timeout $time_out ../bin/lp_solve temp.lp | grep "Value of objective"
    fi
    
    if [ "$solver" = "scip" ]; then
        python ../src/tsp2ilp/tsp2ilp.py --IBMLP temp.graph temp_ibm.lp        
        time timeout $time_out ../bin/scip -f temp_ibm.lp | grep "objective value"
	fi
	
	if [ "$solver" = "held_karp" ]; then
        time timeout $time_out ../bin/tsp_opt < temp.graph
	fi
	
	if [ "$solver" = "held_karp_hash" ]; then
       time timeout $time_out ../bin/held_karp_hash < temp.graph
	fi

	if [ "$solver" = "glpsol" ]; then
        python ../src/tsp2ilp/tsp2ilp.py --IBMLP temp.graph temp_ibm.lp 
        time timeout $time_out ../bin/glpsol --lp temp_ibm.lp | grep "tree is empty"
	fi    
done

