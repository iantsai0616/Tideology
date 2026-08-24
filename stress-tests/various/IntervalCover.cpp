#include "../utilities/template.h"

#include "../../content/various/IntervalCover.h"

bool covers(pii g, vector<pii>& in, int mask){
  vector<pii> a;
  rep(i, 0, sz(in)) if(mask >> i & 1) a.pb(in[i]);
  sort(all(a)); int cur = g.F;
  for(auto [l, r] : a) if(l <= cur) cur = max(cur, r);
  return cur >= g.S;
}

int main(){
  assert(cover(pii(0, 1), vector<pii>{{0, 0}}).empty());
  mt19937 rng(123);
  rep(it, 0, 5000){
    int n = rng()%12; pii g = {(int)(rng()%7)-3, (int)(rng()%7)+1};
    if(g.F > g.S) swap(g.F, g.S);
    vector<pii> in(n);
    for(auto &[l, r] : in){
      l = (int)(rng()%13)-5; r = (int)(rng()%13)-5;
      if(l > r) swap(l, r);
    }
    int best = n+1;
    rep(mask, 0, 1 << n) if(covers(g, in, mask)){
      best = min(best, __builtin_popcount(mask));
    }
    vi got = cover(g, in);
    if(g.F == g.S) assert(got.empty());
    else if(best == n+1) assert(got.empty());
    else{
      assert(sz(got) == best);
      int cur = g.F;
      for(int i : got){
        assert(in[i].F <= cur && cur < in[i].S);
        cur = in[i].S;
      }
      assert(cur >= g.S);
    }
  }
  cout << "Tests passed!\n";
}
