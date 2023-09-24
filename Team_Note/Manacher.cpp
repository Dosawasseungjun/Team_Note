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

//16163 풀이
// dp[i] : i가 중심인 original 팰린드롬의 길이
void manachers(vector<int> &S, int dp[]){
    int n = S.size();
    int r = -1, p = -1;  // radius, position
    for(int i=0;i<n;i++){
        if(i <= r) dp[i] = min( (2 * p - i >= 0 ? dp[2 * p - i] : 0), r - i);
        else dp[i] = 0;

        while(i - dp[i] - 1 >= 0 && i + dp[i] + 1 < n && S[i - dp[i] - 1] == S[i + dp[i] + 1]) dp[i]++;
        if(i + dp[i] > r){
            r = i + dp[i];
            p = i;
        }
    }
}

// dp[i] : i가 중심인 original string 팰린드롬의 길이
void str_manachers(string &S, int dp[]){
    int n = S.size();
    int r = -1, p = -1;  // radius, position
    for(int i=0;i<n;i++){
        if(i <= r) dp[i] = min( (2 * p - i >= 0 ? dp[2 * p - i] : 0), r - i);
        else dp[i] = 0;

        while(i - dp[i] - 1 >= 0 && i + dp[i] + 1 < n && S[i - dp[i] - 1] == S[i + dp[i] + 1]) dp[i]++;
        if(i + dp[i] > r){
            r = i + dp[i];
            p = i;
        }
    }
}
const int MAX = 2e6+1;
int dp[2 * MAX];

int main(){
    fast_io
    string s; cin >> s;
    string ns;
    for(int i=0;i<s.size();i++){
        ns += '@';
        ns += s[i];
    }
    ns += '@';
    str_manachers(ns, dp);
    ll res = 0;
    for(int i=0;i<ns.size();i++) res += (dp[i]+1)/2LL;
    cout << res;
}