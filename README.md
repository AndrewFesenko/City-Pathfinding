# 🏙️ City Pathfinding Simulator

A performance-focused simulation of large-scale city pathfinding using Dijkstra's algorithm and A* search. The simulator allows for testing how real-world conditions like road closures and traffic congestion affect routing efficiency in a city-scale network with 100,000+ intersections.

---

## ⚙️ Core Features

- Graph-based city simulation with up to **100,000 nodes**
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

- Based on [SNAP roadNet datasets](https://snap.stanford.edu/data/)
- Sample nodes/edges stored in `data/nodes.csv` and `data/edges.csv`
- Edge weights simulate distance and traffic conditions
- Large-scale testing supported via generated or converted data
