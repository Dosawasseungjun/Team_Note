#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second


template<int SZ, ll B_MOD> struct Number_Theory{
    vector<ll> fac;
    void precal(int sz = SZ){
        fac = vector<ll> (sz+1);
        fac[0] = 1;
        for(int i=1;i<=sz;i++){
            fac[i] = fac[i-1]*i;
            fac[i] %= B_MOD;
        }
    }
    
    ll fastex(ll a, ll e){
        if(!e) return 1;
        if(e==1) return a%B_MOD;
        ll half = fastex(a, e/2);
        ll ret = half*half%B_MOD;
        if(e&1) ret = (ret*a)%B_MOD;
        return ret;
    }
    
    ll binomial(int n, int k){   // 페르마 소정리, 모듈러 곱셈 역원을 이용한 이항계수
        return (fac[n]*fastex(fac[n-k]*fac[k]%B_MOD, B_MOD-2))%B_MOD;
    }
    
    ll lucas_binomial(ll n, ll k, ll m){ //n, k가 크고 m은 적당할 때 fac[m]까지 만들어 두고
        ll res = 1;
        while(n||k){
            res *= binomial(n%m, k%m, m);
            res %= m;
            n /= m; k/= m;
        }
        return res;
    }

    ll catalan(ll n){ 
        /*카탈란수(C_n)
        길이가 2n인 올바른 괄호 쌍의 수
        노드가 n+1개의 리프를 가진 풀 바이너리 트리의 수
        n+2각형을 n개의 삼각형으로 나누는 방법의 수
        */ 
        
        //return binomial(2*n, n) / (n+1)
        return binomial(2*n, n) * fastex(n+1, B_MOD-2) % B_MOD;
    }
};


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

const int MAX = 5e5+1;
ll dp[MAX];
int cnt[10001];
PrimeControl<MAX, numeric_limits<ll>::max()> pc;

// 아래는 사탕 이라는 문제의 해설
int main() {
    fast_io
    int n; cin >> n;
    vector<int> candy;
    cnt[0] = 1; //cnt 0은 안사는 것도 경우의 수니까 1부터 시작
    for(int i=0;i<n;i++){
        int c; cin >> c;
        if(c){
            if(!cnt[c]) candy.push_back(c);
            cnt[c]++;
        }else{
            cnt[c]++;
        }
    }
        
    ll res =0;
    dp[0] = 1;
    pc.eratos();
    for(int i=0;i<candy.size();i++){
        for(int j=MAX-1;j>=0;j--){
            for(int k=1;k<=cnt[candy[i]];k++){
                if(j-k*candy[i]<0) break;
                dp[j] += dp[j-k*candy[i]];
            }
        }
    }
    
    for(int i=2;i<MAX;i++){
        if(i!=1&&pc.p[i]==i){
            res += dp[i];
        }
    }
    
    cout << res*cnt[0]; // 0원짜리 사는 경우의수 곱해줌
}
