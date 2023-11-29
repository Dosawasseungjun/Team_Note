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

struct sfxarr{
    // counting sort를 이용하여 
	vector<int> getSA(const string& str) {
        int n = (int)str.size(), c = 0;
        vector<int> tmp(n), G(n), posG(n),  Gpos(n), ret(n);
        for (int i = 0; i < n; i++) ret[i] = i;
        sort(ret.begin(), ret.end(), [&](int a, int b) { return str[a] < str[b]; });
        for (int i = 0; i < n; i++) {
            G[i] = c;
            if (i + 1 == n || str[ret[i]] != str[ret[i + 1]]) c++;
        }
        for (int h = 1; h < n && c < n; h <<= 1) {
            for (int i = 0; i < n; i++) posG[ret[i]] = G[i];
            for (int i = n - 1; i >= 0; i--) Gpos[G[i]] = i;
            for (int i = 0; i < n; i++)
                if (ret[i] >= n - h) tmp[Gpos[G[i]]++] = ret[i];
            for (int i = 0; i < n; i++)
                if (ret[i] >= h) tmp[Gpos[posG[ret[i] - h]]++] = ret[i] - h;
            c = 0;
            for (int i = 0; i + 1 < n; i++) {
                int a = (G[i] != G[i + 1]) || (tmp[i] >= n - h)
                        || (posG[tmp[i + 1] + h] != posG[tmp[i] + h]);
                G[i] = c;
                c += a;
                }
                G[n - 1] = c++;
                tmp.swap(ret);
        }
        return ret;
}
    vector<int> lcp(const string& in, const vector<int>& sa) {
        int n = (int)in.size();
        if (n == 0) return vector<int>();
        vector<int> rank(n), height(n - 1);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;
        for (int i = 0, h = 0; i < n; i++) {
            if (rank[i] == 0) continue;
            int j = sa[rank[i] - 1];
            while (i + h < n && j + h < n && in[i + h] == in[j + h]) h++;
            height[rank[i] - 1] = h;
            if (h > 0) h--;
        }
        return height;
    }
};


int main(){
    fast_io
}