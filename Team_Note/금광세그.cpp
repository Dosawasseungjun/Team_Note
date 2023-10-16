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

const int MAXSIZE = 1e5+1;
const ll INF = 1e9+1;

// 금광 세그 - 연속합과 쿼리 코드
template <class T>
class Node_Segtree{
public:
    class Node{
    public: 
        ll left_max, right_max, full_max, sum_max; 

        Node& operator = (const Node & n1){
            left_max = n1.left_max;
            right_max = n1.right_max;
            full_max = n1.full_max;
            sum_max = n1.sum_max;
            return *this;
        }

        Node operator + (const Node & n1){
            Node ret;
            ret.full_max = full_max + n1.full_max;
            ret.left_max = max(left_max, full_max + n1.left_max);
            ret.right_max = max(n1.right_max, right_max + n1.full_max);
            ret.sum_max = max({sum_max, n1.sum_max, right_max + n1.left_max});
            return ret;
        }
    };

    static const int TREESIZE = 4*MAXSIZE;
    Node* tree = new Node[TREESIZE];

    Node_Segtree(){
        for(int i=0;i<TREESIZE;i++) tree[i] = (Node){-INF, -INF, -INF, -INF};
    }
    ~Node_Segtree(){
        delete[] tree;
    }
    void update(T x, T v, T node, T S, T E){
        if(S==E) {
            tree[node] = (Node){v, v, v, v};
            return;
        }
        
        T mid = (S+E)>>1;
        if(x<=mid) update(x, v, 2*node, S, mid);
        else update(x, v, 2*node+1, mid+1, E);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }
    
    Node query(T L, T R, T node, T S, T E){
        if(L>E||R<S) return (Node){-INF, -INF, -INF, -INF};
        if(L<=S&&E<=R) return tree[node];
        T mid = (S+E)>>1;
        return query(L, R, 2*node, S, mid)+query(L, R, 2*node+1, mid+1, E);
    }
};

Node_Segtree<ll> ndsgt;

int main(){
    fast_io
    int N; cin >> N;
    for(int i=1;i<=N;i++){
        ll x; cin >> x;
        ndsgt.update(i, x, 1, 1, N);
    }
    int M; cin >> M;
    while(M--){
        int i, j; cin >> i >> j;
        cout << ndsgt.query(i, j, 1, 1, N).sum_max << '\n';
    }
}