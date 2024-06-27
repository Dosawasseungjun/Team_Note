#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

pll sub(pll u, pll v){
    return {u.xx-v.xx, u.yy-v.yy};
}

ll ccw(pll a, pll b, pll c){
    pll u, v;
    u = sub(b, a);
    v = sub(c, a);
    ll ret = u.xx*v.yy - u.yy*v.xx;
    if(ret) ret /= abs(ret);
    return ret;
}

struct Randomize{
    std::mt19937 rd = mt19937 ((unsigned)chrono::steady_clock::now().time_since_epoch().count());
    
    int random_int(int s, int e){
        uniform_int_distribution<int> rnd(s, e);
        return rnd(rd);
    }
    
}RD;

bool f(pll a, pll b, pll c, pll d, vector<pll> &p){
    bool ret = true;
    int N = p.size()-1;
    for(int i=1;i<=N;i++){
        if((!ccw(a, b, p[i]))||(!ccw(c, d, p[i]))) continue;
        ret = false;
        break;
    }
    return ret;
}

bool chk(pll a, pll b, pll c, pll d, vector<pll> &p){
    bool ret = true;
    int N = p.size()-1;
    // a-b , c-d
    ret = f(a, b, c, d, p);
    if(ret) return ret;
    // a-c, b-d
    ret = f(a, c, b, d, p);
    if(ret) return ret;
    // a-d, b-c
    ret = f(a, d, b, c, p);
    if(ret) return ret;
    
    return ret;
}

int main() {
    fast_io
    int n; cin >> n;
    vector<pll> dot(n+1);
    for(int i=1;i<=n;i++) cin >> dot[i].xx >> dot[i].yy;
    if(n<=4){
        cout << "success";
        return 0;
    }
    
    for(int i=0;i<1000;i++){
        int a = RD.random_int(1, n);
        int b = RD.random_int(1, n);
        while(a==b) b = RD.random_int(1, n);
        int c = RD.random_int(1, n);
        while(a==c||b==c) c = RD.random_int(1, n);
        int d = RD.random_int(1, n);
        while(a==d||b==d||c==d) d = RD.random_int(1, n);
        
        
        if(chk(dot[a], dot[b], dot[c], dot[d], dot)){
            cout << "success";
            return 0;
        }
    }
    cout << "failure";
}
