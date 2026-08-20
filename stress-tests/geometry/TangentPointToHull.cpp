#include "../utilities/template.h"
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/TangentPointToHull.h"

int main(){
  rep(it, 0, 10000){
    vector<P> p;
    rep(i, 0, 20) p.pb(P(rand() % 31 - 15, rand() % 31 - 15));
    p = convexHull(p);
    if(sz(p) < 3) continue;
    P q(50 + rand() % 20, 50 + rand() % 20);
    auto [x, y] = hullTangents(p, q);
    auto side = [&](int id){
      int lo = 0, hi = 0;
      for(P v : p){
        ll c = (p[id] - q).cross(v - q);
        lo |= c < 0; hi |= c > 0;
      }
      return pii(lo, hi);
    };
    assert(side(x) != pii(1, 1));
    assert(side(y) != pii(1, 1));
    assert(x != y);
  }
  cout << "Tests passed!\n";
}
