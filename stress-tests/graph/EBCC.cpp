#include "../utilities/template.h"
#include "../../content/graph/EBCC.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 10000){
    int n=rng()%9+1, m=rng()%20; EBCC e(n); vector<pii> ed;
    rep(i, 0, m){int a=rng()%n, b=rng()%n;if(a==b)continue;e.add_edge(a, b), ed.pb({a, b});}
    e.build();
    rep(k, 0, sz(ed)){
      vi seen(n); queue<int> q; q.push(ed[k].F), seen[ed[k].F]=1;
      while(sz(q)){int u=q.front();q.pop();rep(j, 0, sz(ed)) if(j!=k){
        auto [a, b]=ed[j]; if(a==u and !seen[b]) seen[b]=1, q.push(b);
        if(b==u and !seen[a]) seen[a]=1, q.push(a);
      }}
      assert((bool)e.is_bridge[k]==!seen[ed[k].S]);
    }
    rep(a, 0, n) rep(b, 0, n){
      vi seen(n); queue<int> q; q.push(a), seen[a]=1;
      while(sz(q)){int u=q.front();q.pop();rep(k, 0, sz(ed)) if(!e.is_bridge[k]){
        auto [x, y]=ed[k]; if(x==u and !seen[y]) seen[y]=1, q.push(y);
        if(y==u and !seen[x]) seen[x]=1, q.push(x);
      }}
      assert((e.id[a]==e.id[b])==(bool)seen[b]);
    }
  }
  cout<<"Tests passed!\n";
}
