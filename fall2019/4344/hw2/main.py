from inputreader import InputReader
from router import Router


def initRouters(nodes, paths):
    routers = {}
    index = 0
    for ind in nodes:
        routers[ind] = Router(index, len(nodes), paths)
        index += 1

    return routers


reader = InputReader()
nodes, paths = reader.read("testfile.txt")
routers = initRouters(nodes, paths)
