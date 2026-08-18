# Authored by: tony9402
# Co-authored by: -
# Link: https://leetcode.com/problems/critical-connections-in-a-network/submissions/953575786
class Solution:
    def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:

        # Create the graph
        graph = collections.defaultdict(list)

        for a, b in connections:
            graph[a].append(b)
            graph[b].append(a)

        # Define the properties for Tarjan's algorithm
        idx, lo_link, curr_idx = [None for _ in range(n)], [None for _ in range(n)], 0
        stack, on_stack, unvisited = [], set(), set(range(n))

        # Loop through the unvisited nodes with DFS and find SCC (strongly connected
        # components)
        dfs = [(0, 0)] # Node, predecessor

        while dfs:
            node, predecessor = dfs[-1]
            unvisited.discard(node)

            # Push to stack
            if node not in on_stack:
                stack.append(node)
                on_stack.add(node)

            # Assign the index and low link value
            if idx[node] is None:
                idx[node] = curr_idx
                lo_link[node] = curr_idx
                curr_idx = curr_idx + 1

            # Loop through the neighbors (ignore predecessor)
            for neighbor in graph[node]:
                if neighbor != predecessor:
                    if neighbor in unvisited:
                        dfs.append((neighbor, node))
                        break
                    if neighbor in on_stack:
                        lo_link[node] = min(lo_link[node], lo_link[neighbor])

            # Continue the while loop if there are still neighbors to explore (i. e. top
            # of the DFS stack is different than the current node)
            if dfs[-1][0] != node:
                continue

            # If node is a root node, pop the stack and generate an SCC
            if lo_link[node] == idx[node]:
                while node in on_stack:
                    lo_link[stack[-1]] = lo_link[node]
                    on_stack.remove(stack.pop())

            # This node has been processed (all of its neighbors are visited as well),
			# remove it from the DFS stack
            dfs.pop()

        # Find all the edges that connect different SCCs
        return [[a, b] for a, b in connections if lo_link[a] != lo_link[b]]


""" Solution Description
"""
