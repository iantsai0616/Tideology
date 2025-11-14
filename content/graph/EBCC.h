/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: 
 * Time: O(\log N)
 * Status: stress-tested
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define all(x) x.begin(),x.end()
#define pb push_back
#define F first
#define S second
#define pii pair<int,int>
#define chmax(x,y) x=x>y?x:y;
#define chmin(x,y) x=x<y?x:y;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define vi vector<int>
#define pb push_back
struct EBCC { // 0-based, remember to build
  int n, m, nbcc;
  vector <vector <pii>> g;
  vector <int> pa, low, dep, bcc_id, stk, is_bridge;
  void dfs(int v, int p, int f) {
    low[v] = dep[v] = ~p ? dep[p] + 1 : 0;
    stk.pb(v), pa[v] = p;
    for (auto [u, e] : g[v]) {
      if (low[u] == -1)
        dfs(u, v, e), low[v] = min(low[v], low[u]);
      else if (e != f)
        low[v] = min(low[v], dep[u]);
    }
    if (low[v] == dep[v]) {
      if (~f) is_bridge[f] = true;
      int id = nbcc++, x;
      do {
        x = stk.back(), stk.pop_back();
        bcc_id[x] = id;
      } while (x != v);
    }
  }
  void build() {
    is_bridge.assign(m, 0);
    for (int i = 0; i < n; ++i) if (low[i] == -1)
      dfs(i, -1, -1);
  }
  void add_edge(int u, int v) {
    g[u].emplace_back(v, m), g[v].emplace_back(u, m++);
  }
  EBCC (int _n) : n(_n), m(0), nbcc(0), g(n), pa(n),
    low(n, -1), dep(n), bcc_id(n), stk() {}
};
void solve(){
    int n, m;
    cin >> n >> m;
    EBCC g(n);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g.add_edge(a, b);
    }
    g.build();
    vector<vector<int>>ans(g.nbcc);
    cout << g.nbcc << '\n';
    for(int i = 0; i < n; i++){
        ans[g.bcc_id[i]].pb(i);
    }
    for(int i = 0; i < g.nbcc; i++){
        cout << sz(ans[i]) << ' ' ;
        for(auto x : ans[i]) cout << x << ' ';
        cout << '\n';
    }
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
}
