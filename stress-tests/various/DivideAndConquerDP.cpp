#include "../utilities/template.h"
#include "../../content/various/DivideAndConquerDP.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 10000){
    int n = rng() % 100 + 1;
    vector<ll>w(n), want(n);
    for(ll &x : w) x = rng() % 10000;
    auto cost = [&](int i, int k){ return w[k] + (i - k) * (i - k); };
    auto [dp, opt] = dcDP(n, n, cost);
    rep(i, 0, n){
      want[i] = LLONG_MAX;
      rep(k, 0, i + 1) want[i] = min(want[i], cost(i, k));
      assert(dp[i] == want[i]);
      if(i) assert(opt[i - 1] <= opt[i]);
    }
  }
  cout << "Tests passed!\n";
}
