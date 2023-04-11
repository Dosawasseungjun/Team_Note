#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

const int MAXSIZE = 1e5+1;

// 구간합 세그
template <class T>
class Segtree{
public:
    static const int TREESIZE = 4*MAXSIZE;
    T* tree = new T[TREESIZE];

    Segtree(){
        for(int i=0;i<TREESIZE;i++) tree[i] = 0;
    }
    ~Segtree(){
        delete[] tree;
    }
    T update(T x, T v, T node, T S, T E){
        if(S==E) return tree[node] += v;
        
        T mid = (S+E)>>1;
        if(x<=mid) update(x, v, 2*node, S, mid);
        else update(x, v, 2*node+1, mid+1, E);
        return tree[node] = tree[2*node]+tree[2*node+1];
    }
    T kth(T node, T S, T E, T K){
        if(S==E) return S;
        T mid = (S+E)>>1;
        if(tree[2*node]>=K) return kth(2*node, S, mid, K);
        else return kth(2*node+1, mid+1, E, K-tree[2*node]);
    }
    T query(T L, T R, T node, T S, T E){
        if(L>E||R<S) return 0;
        if(L<=S&&E<=R) return tree[node];
        T mid = (S+E)>>1;
        return query(L, R, 2*node, S, mid)+query(L, R, 2*node+1, mid+1, E);
    }
};

// min 세그
template <class T>
class minSegtree{
public:
    const T MAX = numeric_limits<T>().max();
    static const int TREESIZE = 4*MAXSIZE;
    T* ntree = new T[TREESIZE];

    minSegtree(){
        for(int i=0;i<TREESIZE;i++) ntree[i] = 0;
    }
    ~minSegtree(){
        delete[] ntree;
    }
    void init(T node, T S, T E, vector<T>& a){
        if(S==E){
            ntree[node]  = a[S];
            return;
        }
        int mid = (S+E)>>1;
        init(2*node, S, mid); init(2*node+1, mid+1, E);
        ntree[node] = min(ntree[2*node], ntree[2*node+1]);
    }
    T update(T x, T v, T node, T S, T E){
        if(S==E) return ntree[node] += v;
        
        T mid = (S+E)>>1;
        if(x<=mid) update(x, v, 2*node, S, mid);
        else update(x, v, 2*node+1, mid+1, E);
        return ntree[node] = min(ntree[2*node], ntree[2*node+1]);
    }
    T nquery(T L, T R, T node, T S, T E){
        if(L>E||R<S) return MAX;
        if(L<=S&&E<=R) return ntree[node];
        T mid = (S+E)>>1;
        return min(nquery(L, R, 2*node, S, mid), nquery(L, R, 2*node+1, mid+1, E));
    }
};

// max 세그
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
