
import random
random.seed(20)

import sys

output_file=sys.argv[1]
n=int(sys.argv[2])

with open(output_file, 'w') as f:
    f.write("NAME : UNKNOWN\n")
    f.write("TYPE : TSP\n")
    f.write("DIMENSION : %d\n"%n)
    f.write("EDGE_WEIGHT_TYPE : EUC_2D\n")
    f.write("NODE_COORD_SECTION\n")
    for i in xrange(n):
        line="{0} {1} {2}\n".format(i, random.randint(0,n), random.randint(0,n))
        f.write(line)
   
