#include "../utilities/template.h"

#include "../../content/numerical/Determinant.h"

ll brute(vector<vi>& a){
  int n = sz(a); vi p(n); iota(all(p), 0); ll ans = 0;
  do {
    int inv = 0; ll cur = 1;
    rep(i, 0, n){
      cur *= a[i][p[i]];
      rep(j, 0, i) inv += p[j] > p[i];
    }
    ans += inv&1 ? -cur : cur;
  }while(next_permutation(all(p)));
  return ans;
}

int main(){
  mt19937 rng(123);
  rep(n, 0, 8) rep(it, 0, 1000){
    vector<vi> a(n, vi(n)); vector<vector<double>> b(n, vector<double>(n));
    rep(i, 0, n) rep(j, 0, n) b[i][j] = a[i][j] = (int)(rng()%11)-5;
    assert(llround(det(b)) == brute(a));
  }
  cout << "Tests passed!\n";
}
