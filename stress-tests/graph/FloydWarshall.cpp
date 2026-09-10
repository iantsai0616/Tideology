#include "../utilities/template.h"

#include "../../content/graph/FloydWarshall.h"

int main(){
  mt19937 rng(123);
  rep(it, 0, 1000){
    int n = 1+rng()%15;
    vector<vector<ll>> a(n, vector<ll>(n, inf));
    rep(i, 0, n) rep(j, 0, n) if(i != j && rng()%3 == 0) a[i][j] = rng()%30;
    auto got = a; floydWarshall(got);
    rep(s, 0, n){
      vector<ll> d(n, inf); d[s] = 0;
      priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
      q.push({0, s});
      while(!q.empty()){
        auto [du, u] = q.top(); q.pop();
        if(du != d[u]) continue;
        rep(v, 0, n) if(a[u][v] != inf && d[v] > du+a[u][v]){
          d[v] = du+a[u][v]; q.push({d[v], v});
        }
      }
      assert(got[s] == d);
    }
  }
  vector<vector<ll>> a(5, vector<ll>(5, inf));
  a[0][1] = 1; a[1][2] = -3; a[2][1] = 1; a[2][3] = 2;
  floydWarshall(a);
  rep(i, 0, 3) assert(a[i][1] == -inf && a[i][2] == -inf && a[i][3] == -inf);
  assert(a[4][4] == 0 && a[4][0] == inf);
  cout << "Tests passed!\n";
}
