#include <bits/stdc++.h>

using namespace std;
vector<int> rankOfNode, parent;
vector<pair<double, pair<int, int>>> edgeList, chosenEdges;

int findParent(int x) {
    if (x == parent[x])
        return x;
    return parent[x] = findParent(parent[x]);
}

void link(int x, int y) {
    if (rankOfNode[x] > rankOfNode[y])swap(x, y);
    parent[x] = y;
    if (rankOfNode[x] == rankOfNode[y])rankOfNode[y]++;
}


bool canUnion(int x, int y) {
    x = findParent(x), y = findParent(y);
    if (x != y)
        link(x, y);
    return x != y;
}

void initialize(int n) {
    parent = rankOfNode = vector<int>(n + 1, 1);
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

vector<pair<int, int>> coordinates;

pair<double, pair<int, int>> makeEdge(int node, int edgeFriend) {
    double dist = sqrt(pow(coordinates[node].first - coordinates[edgeFriend].first, 2) +
                       pow(coordinates[node].second - coordinates[edgeFriend].second, 2));
    return {dist, {node, edgeFriend}};

}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, dev;
        cin >> dev >> n;
        coordinates = vector<pair<int, int>>(n + 1);
        for (int i = 1; i <= n; i++)cin >> coordinates[i].first >> coordinates[i].second;
        edgeList = chosenEdges =  vector<pair<double, pair<int, int>>>();
        for (int node = 1; node <= n; node++)
            for (int nodeFriend = node + 1; nodeFriend <= n; nodeFriend++)
                edgeList.push_back(makeEdge(node, nodeFriend));
        long long mst = 0;
        sort(edgeList.begin(), edgeList.end());
        initialize(n);

        for (auto p: edgeList) {
            if (canUnion(p.second.first, p.second.second))
                chosenEdges.push_back(p);
        }
        sort(chosenEdges.rbegin(), chosenEdges.rend());
        if (dev > 1)
            cout <<fixed << setprecision(2) << chosenEdges[dev - 1].first << "\n";
        else
            cout << fixed << setprecision(2) << chosenEdges[0].first << "\n";

    }
        return 0;
}
