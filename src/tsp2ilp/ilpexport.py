

class LPExporter:

    def __init__(self):
        self.lines=[]
    
    def  comment_found(self, comment):
        self.lines.append("/* "+comment+" */\n")
        
    def  empty_line_found(self):
        self.lines.append("\n")
       
    def cost_fun_found(self, cost_fun):
        self.lines.append(cost_fun.toString()+'\n')
            
    def constrain_found(self, constrain):
        self.lines.append(constrain.toString()+'\n')
        
    def bin_vars_found(self, bin_vars):
        self.lines.append("bin "+", ".join(bin_vars)+";\n")
        
    def int_vars_found(self, int_vars):
        self.lines.append("int "+", ".join(int_vars)+";\n")
        
    def get_lines(self):
        return self.lines
        
