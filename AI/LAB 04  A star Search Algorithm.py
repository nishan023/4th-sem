import heapq

def a_star_search(graph, start, goal, heuristic, costs):
    pq = []
    heapq.heappush(pq, (heuristic[start], 0, start))
    visited = set()
    came_from = {start: None}
    g_costs = {start: 0}

    while pq:
        _, current_g, current = heapq.heappop(pq)

        if current in visited:
            continue

        visited.add(current)

        if current == goal:
            path = []
            while current:
                path.append(current)
                current = came_from[current]
            return path[::-1]
        
        for neighbor, cost in graph[current]:
            if neighbor in visited:
                continue

            new_g = current_g + cost
            if neighbor not in g_costs or new_g < g_costs[neighbor]:
                g_costs[neighbor] = new_g
                f = new_g + heuristic[neighbor]
                came_from[neighbor] = current
                heapq.heappush(pq, (f, new_g, neighbor))

    return None

graph = {
    'A': [('B', 1), ('C', 2)],
    'B': [('D', 3)],
    'C': [('E', 2)],
    'D': [('F', 4)],
    'E': [('F', 1)],
    'F': []
}

heuristic = {
    'A': 3,
    'B': 2,
    'C': 1,
    'D': 1,
    'E': 0,
    'F': 0
}

path = a_star_search(graph, 'A', 'F', heuristic, graph)
print(path)
