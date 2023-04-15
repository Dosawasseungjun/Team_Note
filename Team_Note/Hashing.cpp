#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

const int MOD = 1000000007;
template<ll P, ll M> struct Hashing{
    vector<ll> H, B;
    void build(const vector<ll> &S){
        H.resize(S.size()+1);
        B.resize(S.size()+1);
        B[0] = 1;
        for(int i=1;i<=S.size();i++){
            H[i] = (H[i-1]*P+S[i])%M; //누적합 느낌으로
        }
        for(int i=1;i<=S.size();i++){
            B[i] = (B[i-1]*P)%M;
        }
    }
    void insert(const ll val){
        ll nextH =(H.back()*P+val)%M;
        ll nextB = B.back()*P%M;
        H.push_back(nextH);
        B.push_back(nextB);
    }
    void del(){
        H.pop_back();
        B.pop_back();
    }
    ll get(int s, int e){
        ll res= (H[e]-H[s-1]*B[e-s+1])%M;
        return res >= 0 ? res : res+M;
    }
};

template<ll P, ll M> struct String_Hashing{
    vector<ll> H, B;
    void build(const string &S){
        H.resize(S.size()+1);
        B.resize(S.size()+1);
        B[0] = 1;
        for(int i=1;i<=S.size();i++){
            H[i] = (H[i-1]*P+S[i-1])%M; //누적합 느낌으로
        }
        for(int i=1;i<=S.size();i++){
            B[i] = (B[i-1]*P)%M;
        }
    }
    void insert(const ll val){
        ll nextH =(H.back()*P+val)%M;
        ll nextB = B.back()*P%M;
        H.push_back(nextH);
        B.push_back(nextB);
    }
    void del(){
        H.pop_back();
        B.pop_back();
    }
    ll get(int s, int e){
        ll res= (H[e]-H[s-1]*B[e-s+1])%M;
        return res >= 0 ? res : res+M;
    }
};
