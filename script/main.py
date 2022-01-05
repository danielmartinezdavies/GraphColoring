import sys
import random


class Edge:
    start = 0
    end = 0

    def __init__(self, start, end):
        self.start = start
        self.end = end

    def contains(self, e1):
        if self.start == e1.start and self.end == e1.end or self.start == e1.end and self.end == e1.start:
            return True
        return False


if __name__ == '__main__':
    number_vertices = int(sys.argv[1])
    num_edge = int(sys.argv[2])

    # print(random.randint(3, 9))

    print("graph G {")

    edge_list = []
    for i in range(number_vertices):
        print(f"{i};")
    for i in range(number_vertices):
        for j in range(num_edge):
            random_index = random.randint(i + 1, number_vertices)
            p = Edge(i, random_index)
            repeated = False
            for edge in edge_list:
                if p.contains(edge):
                    repeated = True

            if not repeated:
                print(f"{i}--{random_index};")
                edge_list.append(p)
    print("}")
