#include "../utilities/template.h"
#include "../../content/graph/LinkCutTree.h"

int main(){
  {
    LCT<ll, ll> t(4);
    rep(i, 1, 5) t.set_val(i, i), t.set_sval(i, i);
    t.link(2, 1), t.link(3, 1), t.link(4, 3);
    assert(t.query(2, 4)==10 and t.subtree(1, 3)==7);
    t.set_sval(4, 10); assert(t.subtree(1, 3)==13);
  }
  mt19937 rng(1);
  rep(z, 0, 200){
    int n=rng()%20+1; LCT<ll, ll> t(n); vector<set<int>> g(n+1); vi val(n+1);
    rep(i, 1, n+1) val[i]=rng()%100, t.set_val(i, val[i]), t.set_sval(i, val[i]);
    auto path=[&](int s, int e){
      vi p(n+1, -1), q{s}; p[s]=0;
      for(int k=0;k<sz(q);++k) for(int v:g[q[k]]) if(p[v]<0) p[v]=q[k], q.pb(v);
      if(p[e]<0) return pair<bool, ll>{0, 0};
      ll sum=0; for(int u=e;u;u=p[u]){sum+=val[u];if(u==s)break;}
      return pair<bool, ll>{1, sum};
    };
    rep(it, 0, 1000){
      int a=rng()%n+1, b=rng()%n+1, op=rng()%5; auto p=path(a, b);
      if(op==0 and !p.F) t.link(a, b), g[a].insert(b), g[b].insert(a);
      else if(op==1 and g[a].count(b)) t.cut(a, b), g[a].erase(b), g[b].erase(a);
      else if(op==2) val[a]=rng()%100, t.set_val(a, val[a]), t.set_sval(a, val[a]);
      else {
        assert(t.connected(a, b)==p.F);
        if(p.F) assert(t.query(a, b)==p.S);
      }
    }
  }
  cout<<"Tests passed!\n";
}
