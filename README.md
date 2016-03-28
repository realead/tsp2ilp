# tsp2ilp

### About

This is a small investigation whether the freely available MIP solver are up to the task of solving traveling salesman problem.

For this, a directed graph is converted to an Integer Linear Problem, as described in https://en.wikipedia.org/wiki/Travelling_salesman_problem.

Compared solvers are:

   1. glpk-4.59 (https://www.gnu.org/software/glpk)
   2. lp_solve_5.5.2.0 ()
   3. SCIP 3.2.1 (http://scip.zib.de)
    
Other interesting sources are not considered in this investigation:
 
   1. the record holder: http://www.math.uwaterloo.ca/tsp/concorde/index.html
   2. Coin-or branch and cut solver https://projects.coin-or.org/Cbc
   3. other branch and bound approaches, for example see http://stackoverflow.com/questions/7159259/optimized-tsp-algorithms or also http://mat.gsia.cmu.edu/classes/mstc/relax/relax.html

For comparison also some variants of Held-Karp algorithm (see src/solver, https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm) are implemented.

### Usage 

For testing: sh-skripts in ./tools. 

   1. run *sh build.sh* for building the solvers to ./bin.
   2. add links to the lp_solver/scip/glpk standalones to ./bin
   3. run *sh test_pipeline.sh for some testing
   
Using tsp2ilp converter:

   1. As script: input is a list of edges of a graph, output a ILP described in CPLEX LP file format from IBM (http://www.ibm.com/support/knowledgecenter/SSSA5P_12.3.0/ilog.odms.cplex.help/Content/Optimization/Documentation/Optimization_Studio/_pubskel/ps_reffileformatscplex2159.html)
      run **python tsp2ilp.py --IBMLP input_file output_file**
   2. As package: it is possible to use tsp2ilp as a package
   

### Future

   1. testing of Coin-or branch (https://projects.coin-or.org/Cbc)
   2. adjusting solver settings
   2. implementing a specialized branch and bound approach
   3. adding other output formats
   4. improvement of resulting ILPs
   

### Results

All solvers have been running with default settings (1 CPU)

#### Random points in 2d:

                 N=15 (out of 10)              N=20 (out of 10)                N=25 (out of 10)
glpk             0                             not tested                      not tested
lp_solve         5  (less than 200s)           6(less than 300s)
scip             10 (average .9s)              10 (average 3.5s)               10 (average 63s, min 1s, max 130s, less than 500MB needed)
held_karp(opt)   10 (average .01s)             10 (average 0.5s)               10 (average 24s, ca. 8GB needed, hash-version needs more than 10min, no memory savings)

#### Random graphs:

Created by the script ./tools/create_case.py with: 

a) 0.4*n edges per vertex on average, weights 0..100

                 N=15 (out of 10)              N=20 (out of 10)                N=25 (out of 10)         N=40(out of 10, less 60s)    N=100(out of 10, 120s) 
glpk             10 (0s)                       7 (average 0.0 for success)     10 (average 0s)          7                            0
lp_solve         10 (0s)                       10 (0s)                         10 (average 0s)          9                            4
scip             10 (average .9s)              10 (0s)                         10 (0.2s)                10                           8
held_karp(opt)   10 (average .01s)             10 (0.3s)                       10 (average 15s)


b) .4*n edges per vertex on average, all weights 1, seems to be harder to solve for scip but easier for lp_solve
                 N=40 (out of 10, 120s)       N=100 (out of 10)         
glpk             5                            0
lp_solve         10 (0s)                      10(4s)
scip             6                            0

c) .6*n edges per vertex on average, weights 0..100
                 N=40 (out of 10, 120s)       N=100 (out of 10)         
glpk             10 (0.2s)                    0
lp_solve         10 (0.5s)                    3
scip             10 (2.5s)                    8



#### Conclusion

Evaluating the result it should be considered, that all solvers have been used with the default settings and thus may not habe been used in the best possible way. But the expertise needed for adapting the setting exceeds the goals and possibilities of this project.

But even with worst setting one would expect solvers to solve the case with 15 vertices. Only scip managed to do it and thus is the clear winner of this comparison. lp_solve being the clear second as glpk failed to solve any problem in given time.

Held-Karp algorithm beats the linear solvers for the 2d-problems, but has a limit for N=25, as it needs already 8GB. For some instances scip is much faster.

One could surely say, that the used reduction from tsp to ilp seems to be not really suitable to solve problem with ca. 100 nodes if they are comming from 2d points test scenario.

For the test case where any hamiltonian circle should be found (b), lp_solve seems to recognize, that there is no better solution and makes early exit - and beats scip easily.

c) seems to be a harder than a), which is somehow to be expected, as there are more edges and thus more variables.

