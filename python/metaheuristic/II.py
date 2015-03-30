__author__ = 'Ming'


class II():
    def __init__(self, objective_function='', neighbors_choose='best'):
        self.neighbors_choose = neighbors_choose
        if objective_function == '':
            self.objective_function = self.unimplemented
        else:
            self.objective_function = objective_function

    def update_neighbors(self):
        if self.neighbors_choose == 'best':
            pass
        elif self.neighbors_choose == 'first':
            pass

    def unimplemented(self):
        raise Exception('Unimplement Error')

    def run(self):
        print '======================================================='
        print 'Starting II:'
        print 'Objective Function: ' + self.objective_function.func_name
        print 'Neighbors Choose Strategy: ' + self.neighbors_choose
        print '======================================================='

