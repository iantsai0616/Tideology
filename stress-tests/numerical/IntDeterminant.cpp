#include "../utilities/template.h"

#include "../../content/numerical/IntDeterminant.h"

ll brute(vector<vector<ll>> a){
  int n = sz(a); ll prev = 1, sign = 1;
  rep(i, 0, n-1){
    int p = i;
    while(p < n && !a[p][i]) p++;
    if(p == n) return 0;
    if(p != i) swap(a[p], a[i]), sign *= -1;
    rep(j, i+1, n){
      ll x = a[j][i], y = a[i][i];
      rep(k, i+1, n) a[j][k] = (a[j][k]*y-a[i][k]*x)/prev;
    }
    prev = a[i][i];
  }
  return n ? sign*a[n-1][n-1] : 1;
}

int main(){
  mt19937 rng(123);
  rep(n, 0, 8) rep(it, 0, 10000){
    vector<vector<ll>> a(n, vector<ll>(n));
    for(auto &r : a) for(ll &x : r) x = (int)(rng()%11)-5;
    ll m = 1+rng()%10000, ans = brute(a)%m;
    if(ans < 0) ans += m;
    assert(det(a, m) == ans);
  }
  cout << "Tests passed!\n";
}
