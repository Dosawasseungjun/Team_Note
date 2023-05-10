#include <bits/stdc++.h>
#define fast_io cin.tie(NULL); ios_base::sync_with_stdio(false);
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tiii;
#define xx first
#define yy second

const ll MOD = 1e6+3;
class matrix{
public:
    vector<vector<ll>> mat;
    
    void initialize(int a, int b){
        mat.assign(a, vector<ll>(b,0));
    }
    
    void input(int n, int m){
        mat = vector (5*n+1, vector<ll>(5*m+1));
        
    }
    
    matrix operator*(matrix A){
        matrix result;
        result.initialize(mat.size(), A.mat[0].size());
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<A.mat[0].size();j++){
                for(int k=0;k<A.mat.size();k++){
                    result.mat[i][j] += mat[i][k]*A.mat[k][j];
                    result.mat[i][j] %= MOD;
                }
            }
        }
        return result;
    }
    
};

matrix mt;

matrix powMat(matrix &mat, ll b){
    if(b==1){
        return mat;
    }
    
    matrix half = powMat(mat, b/2);
    matrix ret = (half*half);
    if(b&1) return (ret*mat);
    return ret;
}

int main(){
    fast_io
    
}
