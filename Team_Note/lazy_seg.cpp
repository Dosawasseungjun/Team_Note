// lazy propagation segment tree
// 더하기 세그먼트트리
template <class T, int XSZ>
class LazySegtree{
public:
    static const int TREESIZE = 4*XSZ;
    T* tree = new T[TREESIZE];
    T* lazy = new T[TREESIZE];

    LazySegtree(){
        for(int i=0;i<TREESIZE;i++) tree[i] = lazy[i] = 0;
    }
    ~LazySegtree(){
        delete[] tree, lazy;
    }
    void prop(T node, T S, T E){
        if(lazy[node]){
            tree[node] += (E-S+1)*lazy[node];
            if(S!=E){   //아래로 전파
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0; //전파 다했으면 이칸은 0으로
        }
    }
    T update(T L,T R, T v, T node, T S, T E){
        prop(node, S, E);  // 표시 되어있으면 전파하는 과정
        if(R<S||L>E) return;
        if(L<=S&&R>=E){
            tree[node] += (E-S+1)*v;
            if(S!=E){
                lazy[2*node] += v;
                lazy[2*node+1] += v;
            }
            return;
        }
        ll mid = (S+E)>>1;
        update(L, R, v, 2*node, S, mid); update(L, R, v, 2*node+1, mid+1, E);
        tree[node] = tree[2*node]+tree[2*node+1];
    }
    T query(T L, T R, T node, T S, T E){
        prop(node, S, E);
        if(R<S||L>E) return 0;
        if(L<=S&&R>=E) return tree[node];
        ll mid = (S+E)>>1;
        return query(L, R, 2*node, S, mid)+query(L, R, 2*node+1, mid+1, E);
    }
};
