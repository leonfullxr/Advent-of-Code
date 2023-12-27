from collections import defaultdict

class Graph:
    def __init__(self, graph_data):
        self.graph_data = graph_data
        self.parent = {node: None for node in self.graph_data}

    def bfs(self, start, target):
        """
        Perform Breadth-First Search (BFS) to find the path from start to target.
        Returns True if a path exists, False otherwise.
        """
        # Reset parent information for each BFS run
        self.parent = {node: None for node in self.graph_data}
        self.parent[start] = start

        queue = [start]
        while queue:
            current_node = queue.pop(0)
            for adjacent_node, capacity in self.graph_data[current_node].items():
                if capacity > 0 and self.parent[adjacent_node] is None:
                    self.parent[adjacent_node] = current_node
                    queue.append(adjacent_node)
        return self.parent[target] is not None

    def min_cut(self, start, target):
        """
        Apply Ford-Fulkerson algorithm to find the maximum flow (minimum cut) in the graph.
        """
        # Set all edges to have a capacity of 1
        for vertex, edges in self.graph_data.items():
            for edge in edges:
                self.graph_data[vertex][edge] = 1

        max_flow = 0
        while self.bfs(start, target):
            path_flow = float("inf")
            node = target
            while node != start:
                path_flow = min(path_flow, self.graph_data[self.parent[node]][node])
                node = self.parent[node]
            
            max_flow += path_flow

            # Update residual capacities of the edges and reverse edges
            v = target
            while v != start:
                u = self.parent[v]
                self.graph_data[u][v] -= path_flow
                self.graph_data[v][u] += path_flow
                v = u
        return max_flow

    def solve(self):
        group1 = len({node for node, parent in self.parent.items() if parent})
        return (len(self.graph_data) - group1) * group1

def main():
    graph = defaultdict(dict)

    for line in open("input.txt").read().splitlines():
        left, right = line.split(": ")
        for node in right.split():
            graph[left][node] = 1
            graph[node][left] = 1

    g = Graph(graph)

    # Find the target node
    start_node, *other_nodes = graph
    for target_node in other_nodes:
        if g.min_cut(start_node, target_node) == 3:
            break

    print("Part 1:", g.solve())

if __name__ == "__main__":
    main()
