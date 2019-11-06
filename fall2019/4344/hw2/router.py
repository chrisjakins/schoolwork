class Router:

    def __init__(self, index, num, paths):
        self.index_ = index
        self.numRouters_ = num 
        self.distanceTable_ = []
        for i in range(self.numRouters_):
            self.distanceTable_.append([float("inf")] * self.numRouters_)
        # add initial costs
        for path in paths:
            if (path[0] == self.index_ + 1):
                self.distanceTable_[self.index_][path[1] - 1] = path[2]
        self.distanceTable_[self.index_][self.index_] = 0
        self.states_ = [self.distanceTable_]


    def update(self, newpaths):
        print(self.index_)
        return None


    def getStates(self):
        return self.states_
