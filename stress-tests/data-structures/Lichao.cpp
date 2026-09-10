#include "../utilities/template.h"
#include "../../content/data-structures/Lichao.h"

int main(){
  mt19937 rng(1); vector<ll> x(101); iota(all(x), -50);
  LiChao tr(x); vector<tuple<Line, ll, ll>> f;
  rep(it, 0, 10000){
    Line z{(int)rng()%200-100, (int)rng()%10000-5000};
    ll l=x[rng()%sz(x)], r=x[rng()%sz(x)]; if(l>r) swap(l, r);
    if(rng()%2) tr.add(z), l=x.front(), r=x.back(); else tr.add(z, l, r);
    f.pb({z, l, r});
    ll q=x[rng()%sz(x)], ans=4e18;
    for(auto [a, b, c]:f) if(b<=q and q<=c) ans=min(ans, a(q));
    assert(tr.query(q)==ans);
  }
  cout<<"Tests passed!\n";
}
