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

template <class T> struct flow_graph{
    int n;
    struct edge{
        int to, rev;
        T cap;
    };
    vector<vector<edge>> g;  //잔여그래프의 인접리스트
    vector<pii> pos;        //원래방향 간선
    
    flow_graph(int N) : n(N), g(N){}
    
    int add_edge(int u, int v, T cap){
        int u_idx = (int)g[u].size();
        int v_idx = (int)g[v].size();
        if(u==v) v_idx++;
        pos.emplace_back(u, u_idx);
        g[u].emplace_back(edge{v, v_idx, cap});
        g[v].emplace_back(edge{u, u_idx, (T)0});
        return (int)pos.size()-1;
    }
    
    T edmonds_carp(int s, int t){
        T max_flow = 0;
        vector<pii> prv(n);
        const pii init{-1, -1};
        while(1){
            fill(prv.begin(), prv.end(), init);
            prv[s] = {s, -1};
            queue<int> bfsq;
            bfsq.push(s);
            while(!bfsq.empty()){
                int v = bfsq.front();
                bfsq.pop();
                for(int i=0;i<(int)g[v].size();i++){
                    auto& e = g[v][i];
                    if(prv[e.to]!=init||e.cap == 0) continue;
                    prv[e.to] = {v, i};
                    if(e.to==t) break;
                    bfsq.push(e.to);
                }
            }
            if(prv[t]==init) break;
            T path_min = numeric_limits<T>::max();
            for(int v = t;v!=s;v=prv[v].first)
                path_min = min(path_min, g[prv[v].first][prv[v].second].cap);
            max_flow += path_min;
            for(int v = t; v!=s;v= prv[v].first){
                auto& e = g[prv[v].first][prv[v].second];
                auto& rev_e = g[e.to][e.rev];
                e.cap -= path_min;
                rev_e.cap += path_min;
            }
        }
        return max_flow;
    }
};

int main(){
    fast_io
}