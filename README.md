# 🏙️ City Pathfinding Simulator

A performance-focused simulation of large-scale city pathfinding using Dijkstra's algorithm and A* search. The simulator allows for testing how real-world conditions like road closures and traffic congestion affect routing efficiency in a city-scale network with 100,000+ intersections.

---

## ⚙️ Core Features

- Graph-based city simulation with over **100,000 real-world intersections**
- Custom implementations of **Dijkstra** and **A\*** in C++
- Support for **traffic multipliers** and **road closures**
- Coordinate-aware **heuristics for A\*** performance
- Lightweight CLI interface for running experiments

---

## 🧠 Algorithm Overview

### 🔹 Dijkstra

- Explores **all reachable nodes** from the start using the smallest total path cost
- Guarantees the **shortest possible path** (optimal)
- Slower on large graphs when no heuristic is used

### 🔸 A* Search

- Uses a **heuristic** to prioritize nodes closer to the target
- Heuristic used:  
  `sqrt((x1 − x2)^2 + (y1 − y2)^2)` (Euclidean distance)
- Often faster than Dijkstra on spatial graphs
- Still returns the **optimal path** if the heuristic is admissible

---

## 📊 Dataset

- Road network data for **Los Angeles, California**
- Extracted using [`osmnx`](https://github.com/gboeing/osmnx)
- Based on **OpenStreetMap** data
- Exported to CSV using a custom Python script
- Stored in `data/city_edges.csv` (columns: `from`, `to`, `cost`, `x1`, `y1`, `x2`, `y2`)

> Example snippet used to generate the data:
> ```python
> import osmnx as ox
> import csv
> 
> place_name = "Los Angeles, California, USA"
> G = ox.graph_from_place(place_name, network_type="drive")
> 
> with open("data/edges.csv", "w", newline="") as f:
>     writer = csv.writer(f)
>     writer.writerow(["from", "to", "cost", "x1", "y1", "x2", "y2"])
>     for u, v, data in G.edges(data=True):
>         cost = data.get("length", 1.0)
>         x1, y1 = G.nodes[u]["x"], G.nodes[u]["y"]
>         x2, y2 = G.nodes[v]["x"], G.nodes[v]["y"]
>         writer.writerow([u, v, cost, x1, y1, x2, y2])
> ```
