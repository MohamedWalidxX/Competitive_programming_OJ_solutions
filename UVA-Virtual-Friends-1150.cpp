#include <bits/stdc++.h>

using namespace std;
vector<int> rankOfNode, parent, cntFriendsOfCurrentParent;
int findParent(int x) {
    if (x == parent[x])
        return x;
    return parent[x] = findParent(parent[x]);
}

void link(int x, int y) {
    if (rankOfNode[x] > rankOfNode[y])swap(x, y);
    parent[x] = y;
    cntFriendsOfCurrentParent[y] += cntFriendsOfCurrentParent[x];
    cntFriendsOfCurrentParent[x] = 0;
    if (rankOfNode[x] == rankOfNode[y])rankOfNode[y]++;
}

bool canUnion(int x, int y) {
    x = findParent(x), y = findParent(y);
    if (x != y)
        link(x, y);
    return x != y;
}
void initialize(int n){
    parent = vector<int>(n + 1);
    rankOfNode = cntFriendsOfCurrentParent =  vector<int>(n + 1, 1);
    for (int i = 1; i<= n; i++)
        parent[i] = i;
}
int main() {
    int t,e;
    cin >> t;
    while (t--){
        string u,v;
        int nodeId = 1;
        map<string,int>graph;
        // ERROR HERE ??
        initialize(4e5);
        cin >> e;
        while (e--){
            cin >> u >> v;
            if (graph.find(u) == graph.end())
                graph[u] = nodeId++;
            if (graph.find(v) == graph.end())
                graph[v] = nodeId++;
            int x = graph[u], y = graph[v];
            canUnion(x,y);
            cout << max(cntFriendsOfCurrentParent[parent[x]], cntFriendsOfCurrentParent[parent[y]]) << "\n";
        }
    }
    return 0;
}
