class InputReader:

    def read(self, filename):
        try:
            with open(filename) as infile:
                return self.getData(infile)

        except FileNotFoundError:
            return None


    def getData(self, infile):
        paths = []
        for line in infile:
            x = [int(num) for num in line.split(" ")]
            paths.append(x)

        nodes = set()
        for path in paths:
            [nodes.add(x) for x in path[:-1]]

        return list(nodes), paths
