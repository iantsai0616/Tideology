/**
 * Description: dp[i]=min_{k<=i} cost(i, k), assuming opt[i] is monotone.
 * Time: O((N+K) log N) cost calls
 * Status: stress-tested
 */
#pragma once

template<class F>
pair<vector<ll>, vi> dcDP(int n, int k, F cost){
  vector<ll>dp(n, LLONG_MAX);
  vi opt(n);
  auto go = [&](auto self, int l, int r, int ql, int qr)->void{
    if(l >= r) return;
    int m = (l + r) / 2, hi = min(qr, m + 1), who = ql;
    rep(j, ql, hi){
      ll v = cost(m, j);
      if(v < dp[m]) dp[m] = v, who = j;
    }
    opt[m] = who;
    self(self, l, m, ql, who + 1);
    self(self, m + 1, r, who, qr);
  };
  go(go, 0, n, 0, k);
  return {dp, opt};
}
