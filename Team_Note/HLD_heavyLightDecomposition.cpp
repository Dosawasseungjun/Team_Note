#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

const int MAXSIZE = 3e4+1;

template <class T>
class maxSegtree{
public:
    const T MIN = numeric_limits<T>().lowest();
    static const int TREESIZE = 4*MAXSIZE;
    T* xtree = new T[TREESIZE];

    maxSegtree(){
        for(int i=0;i<TREESIZE;i++) xtree[i] = 0;
    }
    ~maxSegtree(){
        delete[] xtree;
    }
    void init(T node, T S, T E, vector<T>& a){
        if(S==E){
            xtree[node]  = a[S];
            return;
        }
        int mid = (S+E)>>1;
        init(2*node, S, mid); init(2*node+1, mid+1, E);
        xtree[node] = max(xtree[2*node], xtree[2*node+1]);
    }
    T update(T x, T v, T node, T S, T E){
        if(S==E) return xtree[node] += v;
        
        T mid = (S+E)>>1;
        if(x<=mid) update(x, v, 2*node, S, mid);
        else update(x, v, 2*node+1, mid+1, E);
        return xtree[node] = max(xtree[2*node], xtree[2*node+1]);
    }
    T xquery(T L, T R, T node, T S, T E){
        if(L>E||R<S) return MIN;
        if(L<=S&&E<=R) return xtree[node];
        T mid = (S+E)>>1;
        return max(xquery(L, R, 2*node, S, mid), xquery(L, R, 2*node+1, mid+1, E));
    }
};

// 경로 중 최대값 찾기
template <class T>
class HLD{
public:
    int n;
    T cost[MAXSIZE], sz[MAXSIZE], dep[MAXSIZE], par[MAXSIZE];
    T top[MAXSIZE], in[MAXSIZE], out[MAXSIZE];
    vector<pair<T, T>> input, inp[MAXSIZE];
    vector<T> adj[MAXSIZE];
    
    bool visited[MAXSIZE];
    
    void dfs(int now = 1){
        visited[now] = 1;
        for(auto [ncost, nxt] : inp[now]){
            if(visited[nxt]) continue;
            adj[now].push_back(nxt);
            cost[nxt] = ncost;
            dfs(nxt);
        }
    }
    
    void dfs1(int now = 1){
        sz[now] = 1;
        for(T& nxt : adj[now]){
            dep[nxt] = dep[now]+1;
            par[nxt] = now;
            dfs1(nxt);
            sz[now] += sz[nxt];
            if(sz[nxt]>sz[adj[now][0]]) swap(nxt, adj[now][0]); //adj[now][0]에는 가장큰것 (heavy)
        }
    }
    
    int tmp = 0;
    void dfs2(int now = 1){
        in[now] = ++tmp;
        for(T nxt : adj[now]){
            top[nxt] = (nxt==adj[now][0] ? top[now] : nxt);
            dfs2(nxt);
        }
        out[now] = tmp;
    }
    
    maxSegtree<T> xst;
    
    // i 번 간선을 val로
    void update(T i, T val){
        if(dep[input[i].xx] < dep[input[i].yy]) swap(input[i].yy, input[i].xx);
        xst.update(in[input[i].xx], val, 1, 1, n);
    }
    
    //u, v위 가장 큰 가중치
    T query(T u, T v){
        T ret = 0;
        while(top[u]!=top[v]){
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            int st = top[u];
            ret = max(ret, xst.xquery(in[st], in[u], 1, 1, n));
            u = par[st];
        }
        if(u==v) return ret;
        if(dep[u] > dep[v]) swap(u, v);
        T nxt = -1;
        for(auto i : adj[u]) if(top[i]==top[u]) nxt = i;
        ret = max(ret, xst.xquery(in[nxt], in[v], 1, 1, n));
        return ret;
    }
    
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = par[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        return u;
    }
};

int main(){
    fast_io
    int n; cin >> n;
    HLD<int> hld;
    hld.n = n;
    for(int i=1;i<n;i++){
        int u, v; cin >> u >> v;
        hld.inp[u].push_back({1, v});
        hld.inp[v].push_back({1, u});
    }
    hld.top[1] = 1;
    hld.dfs(); hld.dfs1(); hld.dfs2();
    int m; cin >> m;
    int last = 1;
    int res = 0;
    while(m--){
        int k; cin >> k;
        int LCA = hld.lca(last, k);
        res += hld.dep[last]+hld.dep[k]-hld.dep[LCA];
        last = k;
    }
    cout << res;
}
