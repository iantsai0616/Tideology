#include "../utilities/template.h"

#include "../../content/graph/MaximumIndependentSet.h"
#include "../../content/graph/MaximumClique.h"

int main(){
  mt19937 rng(123);
  rep(it, 0, 300){
    int n = 1+rng()%19; vb comp(n); vi adj(n);
    rep(i, 0, n) rep(j, i+1, n){
      bool e = rng()%2;
      if(e) adj[i] |= 1 << j, adj[j] |= 1 << i;
      comp[i][j] = comp[j][i] = !e;
    }
    int ans = 0; vector<char> ok(1 << n); ok[0] = 1;
    rep(mask, 1, 1 << n){
      int i = __builtin_ctz(mask), rest = mask ^ (1 << i);
      ok[mask] = ok[rest] && !(adj[i] & rest);
      if(ok[mask]) ans = max(ans, __builtin_popcount(mask));
    }
    assert(sz(Maxclique(comp).maxClique()) == ans);
  }
  cout << "Tests passed!\n";
}
