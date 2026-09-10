#include "../utilities/template.h"
#include "../../content/graph/MinCostMaxFlowCostScaling.h"

struct E {int a, b, cap, cost;};
int main(){
  mt19937 rng(1);
  rep(it, 0, 10000){
    int n=rng()%4+2, s=0, t=n-1, m=rng()%7; vector<E> es;
    CostScalingMCMF f(n);
    rep(i, 0, m){
      int a=rng()%n, b=rng()%n;if(a==b)continue;
      E e{a, b, (int)(rng()%3), (int)(rng()%11)-5}; es.pb(e);
      f.addEdge(e.a, e.b, e.cap, e.cost);
    }
    pair<ll, ll> best{-1, LLONG_MAX}; vi bal(n);
    auto dfs=[&](auto self, int i, ll cost)->void {
      if(i==sz(es)){
        rep(v, 1, n-1) if(bal[v]) return;
        if(bal[s]!=-bal[t] or bal[s]>0) return;
        pair<ll, ll> z{-bal[s], cost};
        if(z.F>best.F or (z.F==best.F and z.S<best.S)) best=z;
        return;
      }
      auto e=es[i];
      rep(x, 0, e.cap+1) bal[e.a]-=x, bal[e.b]+=x, self(self, i+1, cost+x*e.cost), bal[e.a]+=x, bal[e.b]-=x;
    };
    dfs(dfs, 0, 0);
    auto got=f.maxflow(s, t);
    if(got!=best){
      cerr<<"n "<<n<<" got "<<got.F<<' '<<got.S<<" want "<<best.F<<' '<<best.S<<'\n';
      for(auto e:es) cerr<<e.a<<' '<<e.b<<' '<<e.cap<<' '<<e.cost<<'\n';
      assert(0);
    }
  }
  cout<<"Tests passed!\n";
}
