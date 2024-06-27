#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

struct ConvexHullTrick{
    vector<pll> stk;
    vector<int> idx_stk;
    int pos = 0;    //지금 스택에서 어딘지
    double crossPoint(pll line1, pll line2){
        return 1.0 * (line1.yy-line2.yy) / (line2.xx- line1.xx);
    }
    void insert(pll A, int line_idx){
        while(stk.size()-1){
            pll B = stk.back();
            stk.pop_back();
            int Bidx = idx_stk.back();
            idx_stk.pop_back();
            pll C = stk.back();
            
            if(crossPoint(C, B)<=crossPoint(B, A)){
                stk.push_back(B);
                idx_stk.push_back(Bidx);
                break;
            }
        }
        stk.push_back(A);
        idx_stk.push_back(line_idx);
    }
    ll slope(ll k){
        return 0;
    }
    ll y_intercept(ll k){
        return 0;
    }
    ll query(ll x){ // query가 증가수열
        while(pos+1<stk.size()&&crossPoint(stk[pos], stk[pos+1])<x) pos++;
        return stk[pos].xx*x+stk[pos].yy;
    }
    ll binary_query(ll x){
        ll l = 0, r = stk.size();
        while(l+1<r){
            ll mid = (l+r)>>1;
            if(crossPoint(stk[mid-1], stk[mid])<=x) l = mid;
            else r = mid;
        }
        return stk[l].xx*x+stk[l].yy;
    }
    void clear(){
        stk.clear();
        idx_stk.clear();
        pos = 0;
    }
};

int main() {
    fast_io
    
}
