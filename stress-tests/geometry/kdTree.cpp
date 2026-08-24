#include "../utilities/template.h"

#include "../../content/geometry/kdTree.h"

int main(){
  mt19937 rng(123);
  rep(it, 0, 300){
    vector<P> p(1+rng()%100);
    for(P &x : p) x = P((int)(rng()%2001)-1000, (int)(rng()%2001)-1000);
    KDTree kd(p);
    rep(qi, 0, 300){
      P q((int)(rng()%2001)-1000, (int)(rng()%2001)-1000);
      T ans = (q-p[0]).dist2();
      for(P x : p) ans = min(ans, (q-x).dist2());
      auto [dist, point] = kd.nearest(q);
      assert(dist == ans && (q-point).dist2() == ans);
      assert(find(all(p), point) != p.end());
    }
  }
  cout << "Tests passed!\n";
}
