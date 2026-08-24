#include "../utilities/template.h"

#include "../../content/numerical/MatrixInverse-mod.h"

int main(){
  const ll mod = 998244353;
  mt19937 rng(123);
  rep(n, 1, 30) rep(it, 0, 100){
    vector<vector<ll>> a(n, vector<ll>(n));
    rep(i, 0, n) a[i][i] = 1;
    rep(q, 0, 5*n){
      int x = rng()%n, y = rng()%n;
      if(x == y) continue;
      ll c = rng()%mod;
      rep(j, 0, n) a[x][j] = (a[x][j] + c*a[y][j])%mod;
    }
    auto orig = a;
    assert(matInv(a, mod) == n);
    rep(i, 0, n) rep(j, 0, n){
      ll sum = 0;
      rep(k, 0, n) sum = (sum + orig[i][k]*a[k][j])%mod;
      assert(sum == (i == j));
    }
  }
  cout << "Tests passed!\n";
}
