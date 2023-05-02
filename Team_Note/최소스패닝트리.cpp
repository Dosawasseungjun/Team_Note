#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

struct DisjointSet{
    vector<int> parent, rank;
    
    DisjointSet(int n):parent(n+1),rank(n+1, 0){
        for(int i=0;i<=n;i++){
            parent[i] = i;
        }
    }
    
    int find(int u){
        if(u==parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    
    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u==v) return;
        
        if(rank[u]>rank[v]) swap(u, v);
        parent[u] = v;
        if(rank[u]==rank[v]) rank[v]++;
    }
};

template <class T>
struct myGraph{
    static const int V_MAX = 1e5+1;
    int V, E;
    vector<pair<T, T> > adj[V_MAX];
    
    void addEdge(T u, T v, T w){
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    T kruskal(){
        T ret = 0;
        vector<pair<T, pair<T, T>>> edges;    //맨 앞 가중치, 그다음 u->v
        for(int here=1;here<V+1;here++){
            for(int i=0;i<adj[here].size();i++){
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                edges.push_back({cost, make_pair(here, there)});
            }
        }
        
        sort(edges.begin(), edges.end());   //가중치 순으로 정렬 ->시간복잡도를 지배
        DisjointSet dset(V);
        for(int i=0;i<edges.size();i++){
            T cost = edges[i].xx;
            T u = edges[i].yy.xx; T v = edges[i].yy.yy;
            
            if(dset.find(u)==dset.find(v)) continue; // 같은 그룹에 있으면 버려
            dset.merge(u, v);
            ret += cost;
        }
        
        return ret;
    }
};


myGraph<int> G;

int main() {
    fast_io
    cin >> G.V >> G.E;
    for(int i=0;i<G.E;i++){
        int u, v, c; cin >> u >> v >> c;
        G.addEdge(u, v, c);
    }
    cout << G.kruskal();
}
