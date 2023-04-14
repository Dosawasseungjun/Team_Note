#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

//16877 핌버 문제해결과정인데
// mex를 bitset으로 구하는 것과 fibonacii 배열 구하는 것
const int MAX = 3e6+1;
int g[MAX];
vector<int> fibo;
bitset<32> mex;

int main() {
    fast_io
    int n; cin >> n;
    fibo.push_back(1); fibo.push_back(1);
    int now = 0;
    int k = 0;
    while(now<MAX){
        now = fibo[k++] + fibo.back();
        fibo.push_back(now);
    }
    for(int i=1;i<MAX;i++){
        for(int j=0;j<fibo.size()&&fibo[j]<=i;j++){
            mex[g[i-fibo[j]]] = 1;
        }
        while(mex[g[i]]) g[i]++;
        mex.reset();
    }
    
    int G = 0;
    for(int i=0;i<n;i++){
        int k; cin >> k;
        G ^= g[k];
    }
    if(G) cout << "koosaga";
    else cout << "cubelover";
}
