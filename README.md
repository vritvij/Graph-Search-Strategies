# Graph-Search-Strategies
A C++ program to test various graph search strategies like BFS, DFS, UCS and A*

##Input Format: Input.txt
```
Algorithm: (string) The algorithm to use
    Options:
        DFS: Depth first search
        BFS: Breadth first search
        UCS: Uniform cost search
        A* : A* search
Start: (string) The name of the starting node
Goal: (string) The name of the goal node
EdgeCount: (int) Number of edges in the directed graph
Edges: (string[EdgeCount]) The weighted edges in the directed graph
    Format: A B C
        A: (string) The starting node name of the edge
        B: (string) The ending node name of the edge
        C: (int) The weight of the edge
NodeCount: (int) Number of nodes in the directed graph
Nodes: (string[NodeCount]) The nodes in the directed graph 
    Format: X Y
        X: (string) The name of the node
        Y: (string) The heuristic of reaching the goal state from the current node
```

##Output Format: Output.txt
```
Path: (string[]) The nodes along the path along with the path cost till the node
    Format: P Q
        P: The name of the node
        Q: The path cost till from start node to the current node
```

##Examples
```
BFS
Sibiu
Bucharest
5
Sibiu Rimnicu 80
Rimnicu Pitesti 97
Pitesti Bucharest 101
Sibiu Fagaras 99
Fagaras Bucharest 211
5
Sibiu 4
Rimnicu 1
Pitesti 1
Fagaras 1
Bucharest 0
Correct output:
Sibiu 0
Fagaras 1
Bucharest 2
```
```
DFS
Oradea
Bucharest
44
Oradea Zerind 71
Zerind Oradea 71
Oradea Sibiu 151
Sibiu Oradea 151
Zerind Arad 75
Arad Zerind 75
Arad Sibiu 140
Sibiu Arad 140
Arad Timisoara 118
Timisoara Arad 118
Timisoara Lugoj 111
Lugoj Timisoara 111
Lugoj Mehadia 70
Mehadia Lugoj 70
Mehadia Dobreta 75
Dobreta Mehadia 75
Dobreta Craiova 120
Craiova Dobreta 120
Sibiu Fagaras 99
Fagaras Sibiu 99
Sibiu Rimnicu 80
Rimnicu Sibiu 80
Rimnicu Craiova 146
Craiova Rimnicu 146
Rimnicu Pitesti 97
Pitesti Rimnicu 97
Fagaras Bucharest 211
Bucharest Fagaras 211
Pitesti Bucharest 101
Bucharest Pitesti 101
Giurgiu Bucharest 90
Bucharest Giurgiu 90
Neamt Iasi 87
Iasi Neamt 87
Iasi Vaslui 92
Vaslui Iasi 92
Vaslui Urziceni 142
Urziceni Vaslui 142
Bucharest Urziceni 85
Urziceni Bucharest 85
Urziceni Hirsova 98
Hirsova Urziceni 98
Hirsova Eforie 86
Eforie Hirsova 86
20
Arad 366
Craiova 160
Dobreta 242
Eforie 161
Fagaras 176
Giurgiu 77
Hirsova 151
Iasi 226
Lugoj 244
Mehadia 241
Neamt 234
Oradea 380
Pitesti 10
Rimnicu 193
Sibiu 253
Timisoara 329
Urziceni 80
Vaslui 199
Zerind 374
Bucharest 0
```
```
UCS
Arad
Pitesti
22
Oradea Zerind 71
Oradea Sibiu 151
Zerind Arad 75
Arad Sibiu 140
Arad Timisoara 118
Timisoara Lugoj 111
Lugoj Mehadia 70
Mehadia Dobreta 75
Dobreta Craiova 120
Sibiu Fagaras 99
Sibiu Rimnicu 80
Rimnicu Craiova 146
Rimnicu Pitesti 97
Fagaras Bucharest 211
Pitesti Bucharest 101
Giurgiu Bucharest 90
Neamt Iasi 87
Iasi Vaslui 92
Vaslui Urziceni 142
Bucharest Urziceni 85
Urziceni Hirsova 98
Hirsova Eforie 86
20
Arad 366
Bucharest 0
Craiova 160
Dobreta 242
Eforie 161
Fagaras 176
Giurgiu 77
Hirsova 151
Iasi 226
Lugoj 244
Mehadia 241
Neamt 234
Oradea 380
Rimnicu 193
Sibiu 253
Timisoara 329
Urziceni 80
Vaslui 199
Zerind 374
Pitesti 0
```
```
A*
JordanHome
StaplesCenter
8
JordanHome CA73/NewportCoastDr 5
CA73/NewportCoastDr I405/CA73 10
I405/CA73 I110/I405 25
I110/I405 I10/I110 20
I10/I110 I110/I405 30
I10/I110 I10/I405 9
I105/I110 I10/I110 7
I10/I110 StaplesCenter 3
8
JordanHome 55
CA73/NewportCoastDr 45
I405/CA73 40
I110/I405 16
I105/I110 8
I10/I110 2
I10/I405 3
StaplesCenter 0
```
