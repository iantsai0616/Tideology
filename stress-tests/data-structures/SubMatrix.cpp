#include "../utilities/template.h"

#include "../../content/data-structures/SubMatrix.h"

int main(){
  mt19937 rng(123);
  rep(it, 0, 1000){
    int n = 1+rng()%12, m = 1+rng()%12;
    vector<vi> a(n, vi(m));
    for(auto &r : a) for(int &x : r) x = (int)(rng()%101)-50;
    SubMatrix<int> sm(a);
    rep(q, 0, 100){
      int u = rng()%(n+1), d = rng()%(n+1);
      int l = rng()%(m+1), r = rng()%(m+1);
      if(u > d) swap(u, d);
      if(l > r) swap(l, r);
      int ans = 0;
      rep(i, u, d) rep(j, l, r) ans += a[i][j];
      assert(sm.sum(u, l, d, r) == ans);
    }
  }
  cout << "Tests passed!\n";
}
