#include "../utilities/template.h"
#include "../../content/data-structures/MoQueries.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 1000){
    int n=rng()%100+1, q=rng()%200; vi a(n); for(int &x:a)x=rng()%100;
    vector<pii> ask(q); for(auto &[l, r]:ask) l=rng()%n, r=rng()%(n+1), l=min(l, r);
    ll sum=0;
    auto ans=mo(ask, [&](int i, int){sum+=a[i];}, [&](int i, int){sum-=a[i];}, [&]{return sum;}, max(1, (int)(n/sqrt(max(q, 1)))));
    rep(i, 0, q) assert(ans[i]==accumulate(a.begin()+ask[i].F, a.begin()+ask[i].S, 0LL));
  }
  rep(it, 0, 1000){
    int n=rng()%30+1, q=rng()%100; vi p(n), a(n); vector<vi> g(n);
    rep(i, 1, n) p[i]=rng()%i, g[i].pb(p[i]), g[p[i]].pb(i);
    for(int &x:a)x=rng()%100;
    vector<array<int, 2>> ask(q); for(auto &z:ask) z={(int)(rng()%n), (int)(rng()%n)};
    ll sum=0; deque<int> path;
    auto add=[&](int u, int e){sum+=a[u];if(e)path.pb(u);else path.push_front(u);};
    auto del=[&](int u, int e){sum-=a[u];if(e){assert(path.back()==u);path.pop_back();}else{assert(path.front()==u);path.pop_front();}};
    auto ans=moTree(ask, g, add, del, [&]{return sum;}, 0, max(1, (int)(n/sqrt(max(q, 1)))));
    rep(i, 0, q){
      int u=ask[i][0], v=ask[i][1]; vi seen(n); ll want=0;
      for(int x=u;;x=p[x]){seen[x]=1;if(!x)break;}
      while(!seen[v]) want+=a[v], v=p[v];
      while(u!=v) want+=a[u], u=p[u];
      want+=a[u]; assert(ans[i]==want);
    }
  }
  cout<<"Tests passed!\n";
}
