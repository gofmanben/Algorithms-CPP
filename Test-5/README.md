# Test 5 -- Graph Algorithms Study Guide (C++)

This study guide contains **main ideas, C++ code examples, and time
complexity** for the remaining Test 5 graph problems.

## Problems Covered

- [Question 1: Detect Cycle in an Undirected Graph](#1-detect-cycle-in-an-undirected-graph)
- [Question 2: Determine if Edge (u,v) Is Part of a Cycle](#2-determine-if-edge-uv-is-part-of-a-cycle)
- [Question 3: Determine if Directed Graph is a DAG](#3-determine-if-directed-graph-is-a-dag)
- [Question 5: Determine if Vertex v is a Cut Vertex](#5-determine-if-vertex-v-is-a-cut-vertex)
- [Question 6: Why Dijkstra Fails With Negative Edges](#6-why-dijkstra-fails-with-negative-edges)
- [Question 8: Reverse a Directed Graph](#8-reverse-a-directed-graph)
- [Question 11: Pair With Maximum Common Neighbors](#11-pair-with-maximum-common-neighbors)
- [Question 14: Find All Apex Species](#14-find-all-apex-species)
- [Question 17: Find Sink Vertices That Lose Power](#17-find-sink-vertices-that-lose-power-when-station-s-fails)
- [Question 18: Determine if Graph is Semiconnected](#18-determine-if-graph-is-semiconnected)
- [Question 19: Diameter of Graph](#19-diameter-of-graph)

All examples assume the graph is stored as an **adjacency list**.

``` cpp
using Graph = vector<vector<int>>;
```

Where

-   **V** = number of vertices
-   **E** = number of edges

------------------------------------------------------------------------

# 1) Detect Cycle in an Undirected Graph

A cycle is a sequence of vertices v1, v2, . . . , vk such that for each i, (vi, vi+1) is an edge, and (vk,v0) is an edge. Determine if G has a cycle. Try using both BFS and DF if S.

## Main idea

Run BFS or DFS. If a visited neighbor appears that **is not the
parent**, the graph contains a cycle.

## Code

``` cpp
bool hasCycleUndirected(const Graph& adj) {

    int n = adj.size();
    vector<bool> visited(n,false);
    vector<int> parent(n,-1);
    queue<int> q;

    for(int start=0; start<n; start++){

        if(visited[start]) continue;

        visited[start]=true;
        q.push(start);

        while(!q.empty()){

            int u=q.front();
            q.pop();

            for(int v:adj[u]){

                if(!visited[v]){
                    visited[v]=true;
                    parent[v]=u;
                    q.push(v);
                }
                else if(parent[u]!=v){
                    return true;
                }
            }
        }
    }

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

``` cpp
bool edgeInCycle(const Graph& adj,int a,int b){

    int n=adj.size();
    vector<bool> visited(n,false);
    queue<int> q;

    visited[a]=true;
    q.push(a);

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            if((u==a && v==b) || (u==b && v==a))
                continue;

            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    return visited[b];
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 3) Determine if Directed Graph is a DAG

A directed graph is called a DAG if it contains no directed cycles. Determine if a graph is a DAG.

## Main idea

Use DFS with recursion stack detection.

States:

    0 = unvisited
    1 = visiting
    2 = finished

## Code

``` cpp
bool dfsCycle(int u,const Graph& adj,vector<int>& state){

    state[u]=1;

    for(int v:adj[u]){

        if(state[v]==1)
            return true;

        if(state[v]==0 && dfsCycle(v,adj,state))
            return true;
    }

    state[u]=2;

    return false;
}

bool isDAG(const Graph& adj){

    int n=adj.size();
    vector<int> state(n,0);

    for(int i=0;i<n;i++){

        if(state[i]==0){
            if(dfsCycle(i,adj,state))
                return false;
        }
    }

    return true;
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 5) Determine if Vertex v is a Cut Vertex

A vertex v is a cut or articulation vertex if its removal disconnects two other vertices. Equivalently, all paths (in G, before removal) from u to u 0 pass through v. Determine if v is a cut vertex. If so, find some pair (u, u0 ) that got disconnected.

## Main idea

Remove vertex `v`. Run BFS from another vertex.\
If some vertex becomes unreachable, `v` is a cut vertex.

## Code

``` cpp
pair<bool,pair<int,int>> isCutVertex(const Graph& adj,int cut){

    int n=adj.size();
    vector<bool> visited(n,false);
    queue<int> q;

    int start=-1;

    for(int i=0;i<n;i++){
        if(i!=cut){
            start=i;
            break;
        }
    }

    visited[start]=true;
    q.push(start);

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            if(v==cut) continue;

            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    for(int i=0;i<n;i++){
        if(i!=cut && !visited[i])
            return {true,{start,i}};
    }

    return {false,{-1,-1}};
}
```

**Time Complexity**

    O(V + E)

------------------------------------------------------------------------

# 6) Why Dijkstra Fails With Negative Edges

The proof of Dijkstra’s algorithm fails when there are negative edges. Why?

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

Given a directed (unweighted) graph G, the reverse is obtained by simply reversing all edges. Assume G is represented as an adjacency list of out neighbors. Construct the reverse of G.

## Main idea

Reverse every edge.

## Code

``` cpp
Graph reverseGraph(const Graph& adj){

    int n=adj.size();
    Graph rev(n);

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

A common recommendation feature used in social networking websites is the number of common friends. In an undirected graph G, find a pair (u, v) with the largest number of common neighbors.

## Main idea

Check every pair of vertices and count common neighbors.

## Code

``` cpp
pair<int,int> maxCommonNeighbors(const Graph& adj){

    int n=adj.size();
    pair<int,int> best={-1,-1};
    int bestCount=-1;

    vector<bool> mark(n,false);
    vector<int> used;

    for(int u=0;u<n;u++){

        for(int v=u+1;v<n;v++){

            used.clear();

            for(int x:adj[u]){
                if(!mark[x]){
                    mark[x]=true;
                    used.push_back(x);
                }
            }

            int count=0;

            for(int y:adj[v])
                if(mark[y])
                    count++;

            if(count>bestCount){
                bestCount=count;
                best={u,v};
            }

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

Biologists often construct a food network of species in an ecosystem. The vertices represent species, and a directed edge (u, v) means species u eats species v. An apex species is one that is not eaten by another species. Suppose you are given a list of all possible “eating” relationships (so a list of “u eats v”). Determine all apex species.

## Main idea

Apex species = vertices with **indegree = 0**.

## Code

``` cpp
vector<int> findApex(const Graph& adj){

    int n=adj.size();
    vector<int> indegree(n,0);

    for(int u=0;u<n;u++)
        for(int v:adj[u])
            indegree[v]++;

    vector<int> apex;

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

You are given a directed, unweighted graph G representing the power grid, as an adjacency list. Each vertex is a power station, and an edge (u, v) means that power goes from u to v. A source vertex denotes a power generator. A sink vertex denotes a power supplier, typically to a neighborhood. Your job is to understand the robustness of the power grid, under failure of a power station s. (Note that this may not be a source, it could be some internal vertex.) If s fails, it stops transmitting power to any of the outneighbors. This could potentially result in some sink node t not receiving power at all, representing a power failure in a neighborhood. Thus, a sink node t will not receive power if every path from every source to t passes through the power station s. Design an algorithm that given G and a vertex s, determines all the sink vertices t (if any) that stop receiving power when s fails.

## Main idea

Run BFS from **all sources except s**.

Any sink not reached loses power.

## Code

``` cpp
vector<int> sinksFail(const Graph& adj,int s){

    int n=adj.size();
    vector<int> indeg(n,0),outdeg(n,0);

    for(int u=0;u<n;u++){
        outdeg[u]=adj[u].size();
        for(int v:adj[u])
            indeg[v]++;
    }

    vector<bool> visited(n,false);
    queue<int> q;

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

            if(v==s) continue;

            if(!visited[v]){
                visited[v]=true;
                q.push(v);
            }
        }
    }

    vector<int> result;

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

A directed graph G is semiconnected if for all pairs of vertices u, v, there is either a path from u to v, or from v to u(but not both). Give an algorithm to determine if G is semiconnected.

## Main idea

For every pair `(u,v)` check if `u` reaches `v` OR `v` reaches `u`.

## Code

``` cpp
bool isSemiconnected(const Graph& adj){

    int n=adj.size();
    vector<vector<bool>> reach(n,vector<bool>(n,false));

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

The diameter of a graph G is the largest shortest path distance in G (meaning, it is max u,v∈V dist(u,v), where dist(u,v) is the shortest path distance). Give an algorithm to compute the diameter of an undirected graph G. Give a more efficient algorithm to determine the diameter of an undirected tree T.

## Main idea

Run BFS from every vertex and take the largest distance.

## Code

``` cpp
int bfsDist(const Graph& adj,int start){

    int n=adj.size();
    vector<int> dist(n,-1);
    queue<int> q;

    dist[start]=0;
    q.push(start);

    int best=0;

    while(!q.empty()){

        int u=q.front();
        q.pop();

        for(int v:adj[u]){

            if(dist[v]==-1){
                dist[v]=dist[u]+1;
                best=max(best,dist[v]);
                q.push(v);
            }
        }
    }

    return best;
}

int graphDiameter(const Graph& adj){

    int n=adj.size();
    int diameter=0;

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
    2. BFS from A → farthest B
    3. distance(A,B) = diameter

**Time Complexity**

    O(V)
