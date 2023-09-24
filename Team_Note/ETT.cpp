#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
typedef tuple<ll, ll, ll> tlll;
#define xx first
#define yy second

const int V_MAX = 1e5+1;
int N;
int par[V_MAX];
vector<int> adj[V_MAX];


int in[V_MAX], out[V_MAX];
int cnt = 0;
void dfs(int here, int parent){
    in[here] = ++cnt;
    for(int nxt : adj[here]){
        if(nxt == parent) continue;
        dfs(nxt , here);
    }
    out[here] = cnt;
}
