# Pracitce 7.1, A

def find_lowest_cost_node(costs, done_nodes):
    cost = float('inf')
    node = None
    for n in costs:
        if n not in done_nodes and costs[n] < cost:
            cost = costs[n]
            node = n
    return node

if __name__ == '__main__':
    graph = dict()
    graph['start'] = {'A': 5, 'B': 2}
    graph['A'] = {'C': 4, 'D': 2}
    graph['B'] = {'A': 8, 'D': 7}
    graph['C'] = {'D': 6, 'end': 3}
    graph['D'] = {'end': 1}
    graph['end'] = {}

    costs = dict()
    costs['A'] = 5
    costs['B'] = 2
    costs['C'] = float('inf')
    costs['D'] = float('inf')
    costs['end'] = float('inf')

    parents = dict()
    parents['A'] = 'start'
    parents['B'] = 'start'
    parents['C'] = None
    parents['D'] = None
    parents['end'] = None

    done_nodes = []

    cost = float('inf')
    node = find_lowest_cost_node(costs, done_nodes)
    while node:
        cost = costs[node]
        for neighbor in graph[node]:
            if cost + graph[node][neighbor] < costs[neighbor]:
                costs[neighbor] = cost + graph[node][neighbor]
                parents[neighbor] = node
        done_nodes.append(node)
        node = find_lowest_cost_node(costs, done_nodes)
    
    print('Costs:', costs)
    print('Parents:', parents)