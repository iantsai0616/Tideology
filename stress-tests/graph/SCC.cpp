#include "../utilities/template.h"
#include "../../content/graph/SCC.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 20000){
    int n=rng()%9; SCC s(n); vector<vi> r(n, vi(n));
    rep(i, 0, n) r[i][i]=1;
    rep(i, 0, n) rep(j, 0, n) if(rng()%4==0) s.add_edge(i, j), r[i][j]=1;
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) r[i][j]|=r[i][k]&r[k][j];
    s.build();
    rep(i, 0, n) rep(j, 0, n)
      assert((s.sccid[i]==s.sccid[j])==(r[i][j] and r[j][i]));
    rep(i, 0, n) for(int j:s.g[i]) assert(s.sccid[j]<=s.sccid[i]);
  }
  cout<<"Tests passed!\n";
}
