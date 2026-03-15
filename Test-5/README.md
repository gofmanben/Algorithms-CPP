# Test 5 -- Graph Algorithms Study Guide (C++)

This study guide contains **main ideas, C++ code examples, and time
complexity** for the remaining Test 5 graph problems.

## Problems Covered

-   [Question 1: Detect Cycle in an Undirected
    Graph](#1-detect-cycle-in-an-undirected-graph)
-   [Question 2: Determine if Edge (u,v) Is Part of a
    Cycle](#2-determine-if-edge-uv-is-part-of-a-cycle)
-   [Question 3: Determine if Directed Graph is a
    DAG](#3-determine-if-directed-graph-is-a-dag)
-   [Question 5: Determine if Vertex v is a Cut
    Vertex](#5-determine-if-vertex-v-is-a-cut-vertex)
-   [Question 6: Why Dijkstra Fails With Negative
    Edges](#6-why-dijkstra-fails-with-negative-edges)
-   [Question 8: Reverse a Directed Graph](#8-reverse-a-directed-graph)
-   [Question 11: Pair With Maximum Common
    Neighbors](#11-pair-with-maximum-common-neighbors)
-   [Question 14: Find All Apex Species](#14-find-all-apex-species)
-   [Question 17: Find Sink Vertices That Lose
    Power](#17-find-sink-vertices-that-lose-power-when-station-s-fails)
-   [Question 18: Determine if Graph is
    Semiconnected](#18-determine-if-graph-is-semiconnected)
-   [Question 19: Diameter of Graph](#19-diameter-of-graph)

All examples assume the graph is stored as an **adjacency list**.

``` cpp
using Graph = vector<vector<int>>;
```

Where

-   **V** = number of vertices
-   **E** = number of edges

------------------------------------------------------------------------

# 1) Detect Cycle in an Undirected Graph

A cycle is a sequence of vertices v1, v2, . . . , vk such that for each
i, (vi, vi+1) is an edge, and (vk,v0) is an edge. Determine if G has a
cycle. Try using both BFS and DF if S.

## Main idea

Run BFS or DFS. If a visited neighbor appears that **is not the
parent**, the graph contains a cycle.

## Code

```c++
bool hasCycleUndirected(const Graph& adj) {

    int n = adj.size();

    // visited[i] = have we already discovered vertex i?
    vector<bool> visited(n,false);

    // parent[i] = the vertex that first discovered i in BFS tree
    vector<int> parent(n,-1);

    queue<int> q;

    // We loop through every vertex because the graph may be disconnected.
    for(int start=0; start<n; start++){

        // If this component was already explored, skip it.
        if(visited[start]) continue;

        // Start BFS from this component.
        visited[start]=true;
        q.push(start);

        while(!q.empty()){

            int u=q.front();
            q.pop();

            // Explore every neighbor of u.
            for(int v:adj[u]){

                // First time seeing v: mark visited, remember parent, push into queue.
                if(!visited[v]){
                    visited[v]=true;
                    parent[v]=u;
                    q.push(v);
                }
                // If v was already visited and is NOT the parent of u,
                // then we found a back connection => cycle.
                else if(parent[u]!=v){
                    return true;
                }
            }
        }
    }

    // No cycle found in any component.
    return false;
}
```

**Time Complexity:**

    O(V + E)

------------------------------------------------------------------------

# 2) Determine if Edge (u,v) Is Part of a Cycle

Given edge e, determine if G has a cycle involving e.

## Main idea

Remove the edge `(u,v)` and check if `u` can still reach `v`.

## Code

```c++
bool edgeInCycle(const Graph& adj,int a,int b){

    int n=adj.size();
    vector<bool> visited(n,false);
    queue<int> q;

    // Start BFS from one endpoint of the edge.
    visited[a]=true;
    q.push(a);

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            // Pretend the edge (a,b) was removed from the graph.
            if((u==a && v==b) || (u==b && v==a))
                continue;

            // Regular BFS traversal.
            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    // If b is still reachable from a after removing edge (a,b),
    // then there is another path from a to b, so the edge is in a cycle.
    return visited[b];
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 3) Determine if Directed Graph is a DAG

A directed graph is called a DAG if it contains no directed cycles.
Determine if a graph is a DAG.

## Main idea

Use DFS with recursion stack detection.

States:

    0 = unvisited
    1 = visiting
    2 = finished

## Code

```c++
bool dfsCycle(int u,const Graph& adj,vector<int>& state){

    // state[u] = 1 means u is currently in the recursion stack.
    state[u]=1;

    for(int v:adj[u]){

        // If we see a vertex that is already in the recursion stack,
        // then we found a directed cycle.
        if(state[v]==1)
            return true;

        // If v is unvisited, continue DFS from v.
        if(state[v]==0 && dfsCycle(v,adj,state))
            return true;
    }

    // state[u] = 2 means all descendants of u are fully processed.
    state[u]=2;

    return false;
}

bool isDAG(const Graph& adj){

    int n=adj.size();

    // 0 = unvisited, 1 = visiting, 2 = finished
    vector<int> state(n,0);

    // Need to try DFS from every vertex because graph may be disconnected.
    for(int i=0;i<n;i++){

        if(state[i]==0){
            if(dfsCycle(i,adj,state))
                return false; // cycle found => not a DAG
        }
    }

    return true; // no directed cycle found
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 5) Determine if Vertex v is a Cut Vertex

A vertex v is a cut or articulation vertex if its removal disconnects
two other vertices. Equivalently, all paths (in G, before removal) from
u to u 0 pass through v. Determine if v is a cut vertex. If so, find
some pair (u, u0 ) that got disconnected.

## Main idea

Remove vertex `v`. Run BFS from another vertex.\
If some vertex becomes unreachable, `v` is a cut vertex.

## Code

```c++
pair<bool,pair<int,int>> isCutVertex(const Graph& adj,int cut){

    int n=adj.size();
    vector<bool> visited(n,false);
    queue<int> q;

    int start=-1;

    // Pick any vertex different from 'cut' as the BFS start.
    for(int i=0;i<n;i++){
        if(i!=cut){
            start=i;
            break;
        }
    }

    // If graph is too small, there may be no valid start.
    if(start == -1)
        return {false,{-1,-1}};

    // Start BFS while pretending 'cut' was removed.
    visited[start]=true;
    q.push(start);

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            // Skip the removed vertex.
            if(v==cut) continue;

            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    // If some other vertex is unreachable, then 'cut' disconnects the graph.
    for(int i=0;i<n;i++){
        if(i!=cut && !visited[i])
            return {true,{start,i}}; // disconnected pair found
    }

    return {false,{-1,-1}}; // not a cut vertex
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 6) Why Dijkstra Fails With Negative Edges

The proof of Dijkstra's algorithm fails when there are negative edges.
Why?

## Main idea

Dijkstra assumes once a shortest distance is chosen it **cannot decrease
later**.

Example:

    s -> a (2)
    s -> b (5)
    b -> a (-10)

True shortest path:

    s -> b -> a = -5

Dijkstra incorrectly finalizes `a = 2`.

------------------------------------------------------------------------

# 8) Reverse a Directed Graph

Given a directed (unweighted) graph G, the reverse is obtained by simply
reversing all edges. Assume G is represented as an adjacency list of out
neighbors. Construct the reverse of G.

## Main idea

Reverse every edge.

## Code

```c++
Graph reverseGraph(const Graph& adj){

    int n=adj.size();

    // rev will store the reversed graph.
    Graph rev(n);

    // For every edge u -> v in the original graph,
    // add edge v -> u in the reversed graph.
    for(int u=0;u<n;u++){
        for(int v:adj[u]){
            rev[v].push_back(u);
        }
    }

    return rev;
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 11) Pair With Maximum Common Neighbors

A common recommendation feature used in social networking websites is
the number of common friends. In an undirected graph G, find a pair (u,
v) with the largest number of common neighbors.

## Main idea

Check every pair of vertices and count common neighbors.

## Code

```c++
pair<int,int> maxCommonNeighbors(const Graph& adj){

    int n=adj.size();

    // best stores the pair with the largest intersection so far.
    pair<int,int> best={-1,-1};
    int bestCount=-1;

    // mark[x] tells whether x is a neighbor of u.
    vector<bool> mark(n,false);

    // used keeps track of what we marked so we can unmark efficiently.
    vector<int> used;

    for(int u=0;u<n;u++){

        for(int v=u+1;v<n;v++){

            used.clear();

            // Mark all neighbors of u.
            for(int x:adj[u]){
                if(!mark[x]){
                    mark[x]=true;
                    used.push_back(x);
                }
            }

            int count=0;

            // Count how many neighbors of v were also neighbors of u.
            for(int y:adj[v])
                if(mark[y])
                    count++;

            // Update best answer if this pair is better.
            if(count>bestCount){
                bestCount=count;
                best={u,v};
            }

            // Clear marks before checking the next pair.
            for(int x:used)
                mark[x]=false;
        }
    }

    return best;
}
```

**Time Complexity**

    O(V^3)

------------------------------------------------------------------------

# 14) Find All Apex Species

Biologists often construct a food network of species in an ecosystem.
The vertices represent species, and a directed edge (u, v) means species
u eats species v. An apex species is one that is not eaten by another
species. Suppose you are given a list of all possible "eating"
relationships (so a list of "u eats v"). Determine all apex species.

## Main idea

Apex species = vertices with **indegree = 0**.

## Code

```c++
vector<int> findApex(const Graph& adj){

    int n=adj.size();

    // indegree[i] = number of edges coming into vertex i
    vector<int> indegree(n,0);

    // Count incoming edges for each vertex.
    for(int u=0;u<n;u++)
        for(int v:adj[u])
            indegree[v]++;

    vector<int> apex;

    // Apex species are not eaten by anything => indegree = 0
    for(int i=0;i<n;i++)
        if(indegree[i]==0)
            apex.push_back(i);

    return apex;
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 17) Find Sink Vertices That Lose Power When Station s Fails

You are given a directed, unweighted graph G representing the power
grid, as an adjacency list. Each vertex is a power station, and an edge
(u, v) means that power goes from u to v. A source vertex denotes a
power generator. A sink vertex denotes a power supplier, typically to a
neighborhood. Your job is to understand the robustness of the power
grid, under failure of a power station s. (Note that this may not be a
source, it could be some internal vertex.) If s fails, it stops
transmitting power to any of the outneighbors. This could potentially
result in some sink node t not receiving power at all, representing a
power failure in a neighborhood. Thus, a sink node t will not receive
power if every path from every source to t passes through the power
station s. Design an algorithm that given G and a vertex s, determines
all the sink vertices t (if any) that stop receiving power when s fails.

## Main idea

Run BFS from **all sources except s**.

Any sink not reached loses power.

## Code

```c++
vector<int> sinksFail(const Graph& adj,int s){

    int n=adj.size();
    vector<int> indeg(n,0),outdeg(n,0);

    // Compute indegree and outdegree of every vertex.
    for(int u=0;u<n;u++){
        outdeg[u]=adj[u].size();
        for(int v:adj[u])
            indeg[v]++;
    }

    vector<bool> visited(n,false);
    queue<int> q;

    // Start BFS from every source except the failed station s.
    for(int i=0;i<n;i++){
        if(i!=s && indeg[i]==0){
            visited[i]=true;
            q.push(i);
        }
    }

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            // Since s failed, we do not allow traversal through s.
            if(v==s) continue;

            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    vector<int> result;

    // A sink with outdegree 0 that is not reachable anymore loses power.
    for(int i=0;i<n;i++)
        if(i!=s && outdeg[i]==0 && !visited[i])
            result.push_back(i);

    return result;
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 18) Determine if Graph is Semiconnected

A directed graph G is semiconnected if for all pairs of vertices u, v,
there is either a path from u to v, or from v to u(but not both). Give
an algorithm to determine if G is semiconnected.

## Main idea

For every pair `(u,v)` check if `u` reaches `v` OR `v` reaches `u`.

## Code

```c++
bool isSemiconnected(const Graph& adj){

    int n=adj.size();

    // reach[u][v] = can u reach v ?
    vector<vector<bool>> reach(n,vector<bool>(n,false));

    // Run BFS from every start vertex s.
    for(int s=0;s<n;s++){

        queue<int> q;
        reach[s][s]=true;
        q.push(s);

        while(!q.empty()){

            int u=q.front();
            q.pop();

            for(int v:adj[u]){

                if(!reach[s][v]){
                    reach[s][v]=true;
                    q.push(v);
                }
            }
        }
    }

    // For semiconnected graphs, every pair (u,v) must be comparable:
    // either u reaches v OR v reaches u.
    for(int u=0;u<n;u++)
        for(int v=u+1;v<n;v++)
            if(!reach[u][v] && !reach[v][u])
                return false;

    return true;
}
```

**Time Complexity**

    O(V(V+E))

------------------------------------------------------------------------

# 19) Diameter of Graph

The diameter of a graph G is the largest shortest path distance in G
(meaning, it is max u,v∈V dist(u,v), where dist(u,v) is the shortest
path distance). Give an algorithm to compute the diameter of an
undirected graph G. Give a more efficient algorithm to determine the
diameter of an undirected tree T.

## Main idea

Run BFS from every vertex and take the largest distance.

## Code

```c++
int bfsDist(const Graph& adj,int start){

    int n=adj.size();

    // dist[i] = shortest distance from start to i
    vector<int> dist(n,-1);
    queue<int> q;

    dist[start]=0;
    q.push(start);

    int best=0;

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            // First time reaching v gives the shortest distance in an unweighted graph.
            if(dist[v]==-1){
                dist[v]=dist[u]+1;
                best=max(best,dist[v]); // keep farthest distance seen from start
                q.push(v);
            }
        }
    }

    return best; // eccentricity of start
}

int graphDiameter(const Graph& adj){

    int n=adj.size();
    int diameter=0;

    // Run BFS from every vertex and keep the largest shortest-path distance.
    for(int i=0;i<n;i++)
        diameter=max(diameter,bfsDist(adj,i));

    return diameter;
}
```

**Time Complexity**

    O(V(V+E))

------------------------------------------------------------------------

# Faster Diameter for Trees

Algorithm:

    1. BFS from any node → farthest A
       // First BFS finds one end of the longest path
    2. BFS from A → farthest B
       // Second BFS finds the opposite end
    3. distance(A,B) = diameter
       // That distance is the tree diameter

**Time Complexity**

    O(V)

------------------------------------------------------------------------


# Graph Algorithms Cheat Sheet (Patterns for 90% of Problems)

Most graph problems are variations of a **small set of patterns**.  
If you recognize these patterns quickly, you can solve most exam problems.

---

# Pattern 1 — BFS Traversal (Breadth-First Search)

Used for:
- Connectivity
- Shortest path (unweighted)
- Reachability
- Graph diameter
- Power grid problems

```c++
void BFS(const Graph& adj, int start) {

    int n = adj.size();

    // visited[i] tells whether vertex i has already been discovered.
    vector<bool> visited(n,false);

    // BFS uses a queue because it explores level by level.
    queue<int> q;

    // Start from the source vertex.
    visited[start] = true;
    q.push(start);

    while(!q.empty()) {

        // Take the next vertex from the front of the queue.
        int u = q.front();
        q.pop();

        // Explore every neighbor of u.
        for(int v : adj[u]) {

            // If v has not been seen before, discover it now.
            if(!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```

Time Complexity

```
O(V + E)
```

---

# Pattern 2 — BFS With Parent (Cycle Detection)

Key idea:

```
visited[v] == true AND parent[u] != v
```

```c++
bool hasCycle(const Graph& adj) {

    int n = adj.size();

    // visited[i] = was vertex i already discovered?
    vector<bool> visited(n,false);

    // parent[i] = which vertex discovered i in the BFS tree
    vector<int> parent(n,-1);

    queue<int> q;

    // This template starts BFS from vertex 0.
    visited[0]=true;
    q.push(0);

    while(!q.empty()) {

        int u=q.front();
        q.pop();

        for(int v:adj[u]) {

            // First visit to v: record its parent and continue BFS.
            if(!visited[v]) {
                visited[v]=true;
                parent[v]=u;
                q.push(v);
            }
            // If v is already visited and not the parent of u,
            // then we found another route back => cycle.
            else if(parent[u]!=v) {
                return true;
            }
        }
    }

    return false;
}
```

---

# Pattern 3 — DFS Recursion Stack (Depth-First Search)

Used for detecting **directed cycles / DAG checking**.

States

```
0 = unvisited
1 = visiting
2 = finished
```

```c++
bool dfs(int u,const Graph& adj,vector<int>& state){

    // Mark u as active in the current recursion stack.
    state[u] = 1;

    for(int v:adj[u]){

        // Edge to an active vertex means a back edge => cycle.
        if(state[v] == 1)
            return true;

        // Only recurse on vertices not visited yet.
        if(state[v] == 0 && dfs(v,adj,state))
            return true;
    }

    // All descendants of u are processed.
    state[u] = 2;

    return false;
}
```

Time Complexity

```
O(V + E)
```

---

# Pattern 4 — Remove Edge or Vertex

Used for:
- Edge-in-cycle problems
- Cut vertex problems

Skip the removed item during traversal.

Example (remove edge):

```c++
if((u==a && v==b) || (u==b && v==a))
    continue;   // pretend edge (a,b) does not exist
```

Example (remove vertex):

```c++
if(v == removedVertex)
    continue;   // never travel through the removed vertex
```

Then run normal BFS or DFS.

Time Complexity

```
O(V + E)
```

---

# Pattern 5 — Degree Counting

Used for:
- Apex species
- Source nodes
- Sink nodes
- Power grid problems

Compute indegree

```c++
vector<int> indegree(n,0);

// For every edge u -> v,
// increase the number of incoming edges of v.
for(int u=0;u<n;u++)
    for(int v:adj[u])
        indegree[v]++;
```

Concepts

```
Source = indegree 0
Sink   = outdegree 0
Apex   = indegree 0
```

Why it works:
- A **source** has nothing coming into it.
- A **sink** has nothing going out of it.
- An **apex species** is not eaten by anything, so nothing points into it.

---

# Pattern 6 — BFS Distance

Used for:
- Graph diameter
- Shortest path
- Tree diameter

```c++
vector<int> BFSdist(const Graph& adj,int start){

    int n = adj.size();

    // dist[i] = shortest number of edges from start to i
    vector<int> dist(n,-1);

    queue<int> q;

    // Distance from start to itself is 0.
    dist[start] = 0;
    q.push(start);

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            // First time reaching v gives the shortest path in an unweighted graph.
            if(dist[v]==-1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return dist;
}
```

---

# Pattern 7 — All-Pairs Reachability

Used for **semiconnected graph detection**.

```
Run BFS from every vertex
```

```c++
// Pseudocode idea:
for(int i=0;i<V;i++) {
    // Run BFS starting from i
    // Record which vertices are reachable from i
}
```

Why it works:
- After BFS from every vertex, you know reachability for every pair.
- Then for semiconnected graphs, each pair (u,v) must satisfy:
  u reaches v OR v reaches u.

Time Complexity

```
O(V(V+E))
```

---

# Pattern 8 — Reverse Graph

```c++
Graph reverseGraph(const Graph& adj){

    int n = adj.size();

    // rev will store the reversed graph.
    Graph rev(n);

    // Turn every edge u -> v into v -> u.
    for(int u=0;u<n;u++)
        for(int v:adj[u])
            rev[v].push_back(u);

    return rev;
}
```

Time Complexity

```
O(V + E)
```

---

# Pattern 9 — Pair Search

Used for **maximum common neighbors**.

```
// Structure:
for u
   for v
      compare neighbors
```

Why it works:
- Try every possible pair of vertices.
- For each pair, count how many neighbors they share.
- Keep the pair with the maximum count.

Time Complexity

```
O(V^3)
```

---

# Pattern 10 — Tree Diameter Trick

Algorithm

```
// 1st BFS:
1 BFS from any node → farthest A
  // This finds one endpoint of the longest path

// 2nd BFS:
2 BFS from A → farthest B
  // This finds the other endpoint

// Final answer:
3 distance(A,B) = diameter
  // That distance is the tree diameter
```

Time Complexity

```
O(V)
```

---

# Quick Strategy for Graph Problems

1. Identify graph type

```
directed / undirected
weighted / unweighted
tree / general graph
```

2. Choose traversal

```
BFS → shortest paths, reachability
DFS → cycle detection
```

3. Look for keywords

| Keyword | Pattern |
|-------|-------|
| cycle | BFS parent or DFS stack |
| shortest path | BFS |
| remove edge/vertex | BFS skipping |
| sources/sinks | degree counting |
| largest distance | BFS distance |
| reachability | BFS/DFS |
| reverse graph | edge reversal |

---

# The 6 Algorithms You Really Need

```
// Memorize these 6:
1 BFS
2 BFS with parent
3 DFS recursion stack
4 Degree counting
5 BFS distance
6 Edge/vertex skipping
```

Most graph exam problems are combinations of these patterns.
