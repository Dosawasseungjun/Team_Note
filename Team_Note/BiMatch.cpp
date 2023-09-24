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

const int A_MAX = 1e3+1;
const int B_MAX = 1e3+1;
int A[A_MAX], B[B_MAX];
bool visited[A_MAX];
vector<int> adj[A_MAX];

bool DFS(int here){
    if(visited[here]) return false;
    visited[here] = true;
    for(int &there : adj[here]){
        if(B[there] == -1 || DFS(B[there])){
            A[here] = there, B[there] = here;
            return true;
        }
    }
    return false;
}

int BiMatch(){
    fill(A, A + A_MAX, -1);
    fill(B, B + B_MAX, -1);
    int match = 0;
    for(int i=0;i<A_MAX;i++){
        if(A[i] == -1){
            fill(visited, visited + A_MAX, 0);
            match += DFS(i);
        }
    }
    return match;
}
