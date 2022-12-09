import matplotlib.pyplot as plt
import networkx as nx


# create a directed multi-graph
G = nx.MultiDiGraph()
rad = 0


G.add_edges_from([
    (0, 1),
    (1, 5),
    (2, 6),
    (3, 7),
    (4, 5),
    (4, 8),
    (5, 4),
    (5, 6),
    (6, 2),
    (6, 5),
    (6, 7),
    (6, 10),
    (7, 3),
    (7, 6),
    (7, 11),
    (8, 4),
    (8, 9),
    (9, 10),
    (9, 13),
    (10, 6),
    (10, 9),
    (10, 11),
    (11, 7),
    (11, 15),
    (12, 8),
    (13, 9),
    (13, 12),
    (14, 10),
    (14, 12),
    (15, 14),
])


plt.figure(figsize=(16,8)) # plotting a frame
nx.draw(G, connectionstyle=f'arc3, rad = {rad}', with_labels = True) # plotting the graph
plt.show()  # pause before exiting


G.clear()