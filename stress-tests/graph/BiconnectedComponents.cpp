#include "../utilities/template.h"
#include "../../content/graph/BiconnectedComponents.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 10000){
    int n=rng()%9+1, m=rng()%20; BCC b(n); vector<pii> ed;
    rep(i, 0, m){int x=rng()%n, y=rng()%n;if(x==y)continue;b.add_edge(x, y), ed.pb({x, y});}
    b.build();
    rep(c, 0, n){
      auto comps=[&](int ban){
        vi seen(n); int z=0;
        rep(s, 0, n) if(s!=ban and !seen[s]){
          ++z; queue<int> q; q.push(s), seen[s]=1;
          while(sz(q)){int u=q.front();q.pop();for(auto [x, y]:ed){
            if(x==ban or y==ban) continue;
            if(x==u and !seen[y]) seen[y]=1, q.push(y);
            if(y==u and !seen[x]) seen[x]=1, q.push(x);
          }}
        }
        return z;
      };
      int base=comps(-1), after=comps(c);
      assert(b.is_cut(c)==(after>base));
    }
    for(auto &v:b.comp) assert(sz(v)>=2 or (sz(v)==1 and b.g[v[0]].empty()));
  }
  BCC b(2); b.add_edge(0, 1), b.add_edge(0, 1), b.build();
  assert(!b.is_cut(0) and !b.is_cut(1) and b.nbcc==1);
  cout<<"Tests passed!\n";
}
