#include "bits/stdc++.h"
#ifndef WIN32
#define AUTO "%lld"
#else
#define AUTO "%I64d"
#endif
using namespace std;
typedef bool boolean;
#define inf 0xfffffff
#define smin(a, b) (a) = min((a), (b))
#define smax(a, b) (a) = max((a), (b))
template<typename T>
inline boolean readInteger(T& u) {
    char x;
    int aFlag = 1;
    while(!isdigit((x = getchar())) && x != '-' && x != -1);
    if(x == -1)    {
        ungetc(x, stdin);
        return false;
    }
    if(x == '-') {
        aFlag = -1;
        x = getchar();
    }
    for(u = x - '0'; isdigit((x = getchar())); u = u * 10 + x - '0');
    u *= aFlag;
    ungetc(x, stdin);
    return true;
}

typedef class union_found{
public:
    int *f;
    int points;
    union_found():f(NULL), points(0) {}
    union_found(int points):points(points) {
        f = new int[(const int)(points + 1)];
    }
    int find(int x) {
        if(f[x] != x)    return f[x] = find(f[x]);
        return f[x];
    }
    void unit(int fa, int so) {
        int ffa = find(fa);
        int fso = find(so);
        f[fso] = ffa;
    }
    boolean connected(int a, int b) {
        return find(a) == find(b);
    }
    void clear() {
        for(int i = 0; i <= points; i++)
            f[i] = i;
    }
}union_found;

typedef class Edge {
public:
    int from;
    int end;
    int g;
    int s;
    Edge(int from = 0, int end = 0, int g = 0, int s = 0):from(from), end(end), g(g), s(s) {    }
}Edge;
int n, m;
long long G, S;
Edge* edges;

inline void init() {
    readInteger(n);
    readInteger(m);
    readInteger(G);
    readInteger(S);
    edges = new Edge[(const int)(m + 1)];
    for(int i = 1; i <= m; i++) {
        readInteger(edges[i].from);
        readInteger(edges[i].end);
        readInteger(edges[i].g);
        readInteger(edges[i].s);
    }
}

boolean cmp(const Edge& a, const Edge& b) {
    if(a.g != b.g)    return a.g < b.g;
    return a.s < b.s;
}
int top = 0;
Edge *x;
union_found uf;
long long g0 = 0, s0 = 0;
long long res = (1LL << 61);
inline void solve() {
    x = new Edge[(const int)(n + 5)];
    sort(edges + 1, edges + m + 1, cmp);
    uf = union_found(n);
    for(int i = 1; i <= m; i++) {
        uf.clear();
        x[++top] = edges[i];
        for(int j = top; j > 1; j--)
            if(x[j].s < x[j - 1].s)
                swap(x[j], x[j - 1]);
        g0 = 0, s0 = 0;
        int fin = 0;
        for(int j = 1; j <= top; j++) {
            if(!uf.connected(x[j].from, x[j].end)) {
                x[++fin] = x[j];
                smax(g0, (long long)x[j].g);
                smax(s0, (long long)x[j].s);
                uf.unit(x[j].from, x[j].end);
                if(fin == n - 1)    break;
            }
        }
        if(fin == n - 1)
            smin(res, g0 * G + s0 * S);
        top = fin;
    }
    if(res == (1LL << 61))
        printf("-1\n");
    else printf(AUTO"\n", res);
}

int main() {
    init();
    solve();

}