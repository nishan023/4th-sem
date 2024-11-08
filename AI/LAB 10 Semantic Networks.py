import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
G.add_edges_from([('Dog', 'Mammal'), ('Mammal', 'Animal')])

nx.draw(G, with_labels=True)
plt.show()
