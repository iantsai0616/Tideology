#include "../utilities/template.h"
#include "../../content/graph/Dominatortree.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 10000){
    int n=rng()%9+1, s=rng()%n; DominatorTree d(n); vector<vi> g(n);
    rep(i, 0, n) rep(j, 0, n) if(rng()%4==0) d.add_edge(i, j), g[i].pb(j);
    d.build(s);
    auto reach=[&](int ban){
      vi z(n); if(s==ban) return z;
      queue<int> q; q.push(s), z[s]=1;
      while(sz(q)){int u=q.front();q.pop();for(int v:g[u]) if(v!=ban and !z[v]) z[v]=1, q.push(v);}
      return z;
    };
    auto base=reach(-1); vector<vi> without(n);
    rep(x, 0, n) without[x]=reach(x);
    rep(v, 0, n){
      if(!base[v]){assert(d.dom[v]==-1);continue;}
      if(v==s){assert(d.dom[v]==s);continue;}
      vi strict;
      rep(x, 0, n) if(x!=v and !without[x][v]) strict.pb(x);
      int want=-1;
      for(int x:strict){
        bool ok=1; for(int y:strict) if(y!=x and without[y][x]) ok=0;
        if(ok) want=x;
      }
      assert(d.dom[v]==want);
    }
  }
  cout<<"Tests passed!\n";
}
