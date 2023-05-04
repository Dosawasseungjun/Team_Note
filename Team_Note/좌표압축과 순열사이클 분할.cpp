#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

//좌표압축(vector)  //0~n-1까지
template<class T>
void zip(vector<T> &ori, vector<T> &com){
    int n = ori.size();
    sort(ori.begin(), ori.end());
    ori.erase(unique(ori.begin(), ori.end()), ori.end());
    for(int i=0;i<n;i++){
        com[i] = lower_bound(ori.begin(), ori.end(), com[i])-ori.begin()+1; //1부터할지 0부터할지 알아서하기
    }
}


//좌표압축(vector)  //1~n까지
template<class T>
void zip_oneToN(vector<T> &ori, vector<T> &com ){
    const T minusINF = numeric_limits<T>().lowest();
    ori[0] = minusINF;
    int n = ori.size();
    sort(ori.begin(), ori.end());
    ori.erase(unique(ori.begin(), ori.end()), ori.end());
    for(int i=1;i<n;i++){
        com[i] = lower_bound(ori.begin(), ori.end(), com[i])-ori.begin();
    }
}




//순열 사이클 분할(배열을 집어넣기)
const int MAX = 1e5+1;
bool pcd_visited[MAX];
template<class T>
pair<T, T> permution_cycle_decomposition(int n, const T arr[]){
    T cycle_cnt = 0, t_cnt = 1;
    //cycle_cnt는 cycle 개수
    //t_cnt는 cycle이 원래대로 돌아오기 위한 연산 횟수
    
    for(int i=1;i<=n;i++){
        if(!pcd_visited[i]){
            int k =0;
            cycle_cnt++;
            for(int j=i;!pcd_visited[j];j=arr[j]){
                pcd_visited[j] = true;
                k++;
            }
            t_cnt = t_cnt/gcd(t_cnt, k)*k;  //lcm
        }
    }
    return {cycle_cnt, t_cnt};
}

//순열 사이클 분할(vector를 집어넣기)
//const int MAX = 1e5+1;
//bool pcd_visited[MAX];
template<class T>
pair<T, T> permution_cycle_decomposition(int n, const vector<T> &arr){
    T cycle_cnt = 0, t_cnt = 1;
    //cycle_cnt는 cycle 개수
    //t_cnt는 cycle이 원래대로 돌아오기 위한 연산 횟수
    
    for(int i=1;i<=n;i++){
        if(!pcd_visited[i]){
            int k =0;
            cycle_cnt++;
            for(int j=i;!pcd_visited[j];j=arr[j]){
                pcd_visited[j] = true;
                k++;
            }
            t_cnt = t_cnt/gcd(t_cnt, k)*k;  //lcm
        }
    }
    return {cycle_cnt, t_cnt};
}
