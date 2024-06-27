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

int main(){
    fast_io    
    int n; cin >> n;
    vector<pll> v(n);
    for(int i=0;i<n;i++) cin >> v[i].xx >> v[i].yy;
    pll k;
    cin >> k.xx >> k.yy;
    sort(v.begin(), v.end(), [&](const pll &a, const pll &b){
        if((a > k) ^ (b > k))  return a > b;
        if(ccw(k, a, b) != 0) return ccw(k, a, b) > 0;
        ll p = k.xx - a.xx;
        ll q = k.yy - a.yy;
        ll s = k.xx - b.xx;
        ll t = k.yy - b.yy;
        return p * p + q* q < s*s + t*t;
    });
    for(auto [x, y] : v){
        cout << x << ' ' << y << '\n';
    }
}