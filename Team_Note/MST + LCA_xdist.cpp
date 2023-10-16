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
    static const int V_MAX = 5e4+1;
    static const int bit_MAX = 17;
    int V, E;
    vector<pair<T, T> > adj[V_MAX];

    //LCA
    // T par[bit_MAX][V_MAX], ndist[bit_MAX][V_MAX], xdist[bit_MAX][V_MAX], dep[V_MAX];
    T par[bit_MAX][V_MAX], xdist[bit_MAX][V_MAX], dep[V_MAX];

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

    void dfs(T here, T parent, T d){
        dep[here] = d ;
        par[0][here] = parent;
        for (auto [there, cost] : adj[here]){
            if(there == parent) continue;
            //ndist[0][there] = cost; xdist[0][there] = cost;  // 거리 구하고 싶을 때
            xdist[0][there] = cost;
            dfs(there, here, d + 1);
        }
    }

    void setFP(){
        dfs(1, 1, 1);
        // ndist[0][1] = INF;
        for(int j=1;j<bit_MAX;j++){
            for(int i=1;i<=V;i++){
                par[j][i] = par[j-1][par[j-1][i]];
                // ndist[j][i] = min(ndist[j-1][i], ndist[j-1][par[j-1][i]]);
                xdist[j][i] = max(xdist[j-1][i], xdist[j-1][par[j-1][i]]);
            }
        }
    }


    //지금은 경로의 최댓값을 구하는 과정
    T LCA(T u, T v){
        T ret = 0; // xdist를 구하고 싶으면 0, 아니면 INF
        if(dep[u] < dep[v]) swap(u, v);
        T diff = dep[u] - dep[v];

        for(int i=0;i<bit_MAX;i++) if(diff & (1 << i)){
            ret = max(ret, xdist[i][u]);
            u = par[i][u];
        }
        if(u == v) return ret;
        for(int i = bit_MAX-1;i>=0;i--) if(par[i][u] != par[i][v]){
            ret = max(ret, xdist[i][u]);
            u = par[i][u];
            ret = max(ret, xdist[i][v]);
            v = par[i][v];
        }
        ret = max(ret, xdist[0][u]);
        ret = max(ret, xdist[0][v]);
        return ret;
    }
};



myGraph<int> G;

int main() {
    fast_io
    cin >> G.V >> G.E;
    for(int i=0;i<G.E;i++){
        int u, v, w; cin >> u >> v >> w;
        G.addEdge(u, v, w);
    }
    G.kruskal();
}