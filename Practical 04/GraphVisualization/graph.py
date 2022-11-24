import matplotlib.pyplot as plt
import networkx as nx


# create a directed multi-graph
G = nx.MultiDiGraph()
G.add_edges_from([
    (1, 2),
    (2, 3),
    (3, 2),
    (2, 1),
])


# plot the graph
plt.figure(figsize=(8,8))
nx.draw(G, connectionstyle='arc3, rad = 0.1')
plt.show()  # pause before exiting