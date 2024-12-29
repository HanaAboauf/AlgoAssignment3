#include "bits/stdc++.h"
using namespace std;

const int INF = 0xfffffff;

void smax(long long& a, long long b) {
    a = max(a, b);
}

void smin(long long& a, long long b) {
    a = min(a, b);
}

class UnionFind {
public:
    vector<int> parent;
    int size;

    UnionFind(int n) : size(n), parent(n + 1) {
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            parent[rootB] = rootA;
        }
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    void clear() {
        for (int i = 0; i <= size; ++i) {
            parent[i] = i;
        }
    }
};

class Edge {
public:
    int from, to, g, s;
    Edge(int from = 0, int to = 0, int g = 0, int s = 0)
            : from(from), to(to), g(g), s(s) {}
};

vector<Edge> edges;

bool cmp( Edge& a,  Edge& b) {
    if (a.g != b.g) return a.g < b.g;
    return a.s < b.s;
}

void minimalCost(int n,long long G,long long S) {
    vector<Edge> x;
    sort(edges.begin(), edges.end(), cmp);
    UnionFind uf(n);
    long long g0 = 0, s0 = 0;
    long long res = numeric_limits<long long>::max();

    for (const auto& edge : edges) {
        uf.clear();
        x.push_back(edge);
        for (int j = x.size() - 1; j > 0; --j) {
            if (x[j].s < x[j - 1].s) {
                swap(x[j], x[j - 1]);
            }
        }

        g0 = 0;
        s0 = 0;
        int fin = 0;

        vector<Edge> temp;
        for (const auto& e : x) {
            if (!uf.connected(e.from, e.to)) {
                temp.push_back(e);
                smax(g0, (long long)e.g);
                smax(s0, (long long)e.s);
                uf.unite(e.from, e.to);
                if (++fin == n - 1) break;
            }
        }

        x = temp;

        if (fin == n - 1) {
            smin(res, g0 * G + s0 * S);
        }
    }

    if (res == numeric_limits<long long>::max()) {
        cout << "-1\n";
    } else {
        cout << res << "\n";
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    long long G, S;

    cin >> n >> m >> G >> S;

    edges.resize(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].g >> edges[i].s;
    }
    minimalCost(n,G, S);
    return 0;
}
