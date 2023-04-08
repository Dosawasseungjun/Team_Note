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

class Segtree{
public:
    static const int TREESIZE = 4*MAXSIZE;
    ll* tree = new ll[TREESIZE];

    Segtree(){
        for(int i=0;i<TREESIZE;i++) tree[i] = 0;
    }
    ~Segtree(){
        delete[] tree;
    }
    ll update(ll x, ll v, ll node, ll S, ll E){
        if(S==E) return tree[node] += v;
        
        ll mid = (S+E)>>1;
        if(x<=mid) update(x, v, 2*node, S, mid);
        else update(x, v, 2*node+1, mid+1, E);
        return tree[node] = tree[2*node]+tree[2*node+1];
    }
    ll kth(ll node, ll S, ll E, ll K){
        if(S==E) return S;
        ll mid = (S+E)>>1;
        if(tree[2*node]>=K) return kth(2*node, S, mid, K);
        else return kth(2*node+1, mid+1, E, K-tree[2*node]);
    }
    ll query(ll L, ll R, ll node, ll S, ll E){
        if(L>E||R<S) return 0;
        if(L<=S&&E<=R) return tree[node];
        ll mid = (S+E)>>1;
        return query(L, R, 2*node, S, mid)+query(L, R, 2*node+1, mid+1, E);
    }
};
