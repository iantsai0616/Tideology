#include "../utilities/template.h"

#include "../../content/various/KnuthDP.h"

int main(){
  mt19937 rng(123);
  rep(n, 2, 70) rep(it, 0, 100){
    vi sum(n+1);
    rep(i, 0, n) sum[i+1] = sum[i]+1+rng()%20;
    vector<vi> slow(n+1, vi(n+1)), fast = slow, opt(n+1, vi(n+1));
    rep(i, 0, n) opt[i][i+1] = i+1;
    rep(len, 2, n+1) rep(l, 0, n-len+1){
      int r = l+len, cost = sum[r]-sum[l];
      slow[l][r] = INT_MAX;
      rep(k, l+1, r) slow[l][r] = min(slow[l][r], slow[l][k]+slow[k][r]+cost);
      fast[l][r] = INT_MAX;
      rep(k, opt[l][r-1], opt[l+1][r]+1){
        int val = fast[l][k]+fast[k][r]+cost;
        if(val < fast[l][r]) fast[l][r] = val, opt[l][r] = k;
      }
      assert(fast[l][r] == slow[l][r]);
    }
  }
  cout << "Tests passed!\n";
}
