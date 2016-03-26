

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
        
        
class IBMLPExporter:
    def __init__(self):
        self.lines=[]
        self.first_constrain=True
    
    def  comment_found(self, comment):
        pass # no comments
        
    def  empty_line_found(self):
        pass # no lines
       
    def cost_fun_found(self, cost_fun):
        if cost_fun.isMax():
            self.lines.append("MAXIMIZE\n")
        else:
            self.lines.append("MINIMIZE\n")
        self.lines.append(' obj: '+cost_fun.getObjectiveAsString()+'\n')
            
    def constrain_found(self, constrain):
        if self.first_constrain:
            self.lines.append('Subject To\n')
            self.first_constrain=False            
        self.lines.append(' '+constrain.toString()+'\n')
        
    def bin_vars_found(self, bin_vars):
        self.lines.append('BINARY\n')
        self.lines.append(' '+" ".join(bin_vars)+"\n")
        
    def int_vars_found(self, int_vars):
        self.lines.append('GENERAL\n')
        self.lines.append(' '+" ".join(int_vars)+"\n")
        
    def get_lines(self):
        self.lines.append('END\n')
        return self.lines
