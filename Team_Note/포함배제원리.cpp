#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

template<int SZ, ll MOD> struct PrimeControl{
    vector<ll> P;
    ll p[SZ+1];
    // p[i] = i면 소수 - 물론 1은 제외
    // P[i] != i면 합성수고 i를 인수로 가짐
    void eratos(int sz = SZ){
        p[1] = 1;
        for(ll i=2;i<sz;i++){
            if(p[i]) continue;
            p[i] = i;
            P.push_back(i);
            for(ll j=i*i;j<sz;j += i) p[j] = i;
        }
    }
    // n을 소인수 분해
    vector<int> factorization(int n){
        vector<int> ret;
        while(n!=1){
            ret.push_back(p[n]);
            n /= p[n];
        }
        return ret;
    }
};

template<class T, ll MOD>
struct inclusion_exclusion{
    vector<T> p;
    
    void precal(T sz){
        //지금은 소인수만 넣어두는 식으로 했음
        T tmp = sz;
        for(int i=2;i==2||i*i<=tmp;i++){
            if(tmp%i) continue;
            if(!(tmp%i)) while(!(tmp%i)) tmp /= i;
            p.push_back(i);
        }
        if(tmp!=1) p.push_back(tmp);
    }
    
    T iep(T x, T k){  // k보다 작거나 같은데 x와 서로소인 것의 개수
        precal(x);  //x의 소인수를 p에 저장
        T ret = 0;
        int sz = p.size();
        for(int i=0;i<(1<<sz);i++){
            ll lcm = 1;
            ll cnt = 1;
            for(int j=0;j<sz;j++){
                if(i&(1<<j)){
                    cnt *= -1;
                    lcm = std::lcm(lcm, p[j]);
                }
            }
            ret += cnt*(k/lcm);
            ret = (ret%MOD+MOD)%MOD;
        }
        return ret;
    }
};