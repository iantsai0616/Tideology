#include "../utilities/template.h"

#include "../../content/geometry/3dHull.h"
#include "../../content/geometry/PolyhedronVolume.h"

int main(){
  vector<P3> p = {P3(0, 0, 0), P3(1, 0, 0), P3(0, 1, 0), P3(0, 0, 1)};
  auto fs = hull3d(p);
  assert(sz(fs) == 4);
  for(F f : fs) for(P3 x : p){
    assert(f.q.dot(x) <= f.q.dot(p[f.a])+1e-9);
  }
  assert(abs(signedPolyVolume(p, fs) - 1.0/6) < 1e-9);
  mt19937 rng(123);
  rep(it, 0, 100){
    vector<P3> a;
    rep(i, 0, 20) a.pb(P3((int)rng()%1000, (int)rng()%1000, (int)rng()%1000));
    auto hull = hull3d(a);
    for(F f : hull) for(P3 x : a){
      assert(f.q.dot(x) <= f.q.dot(a[f.a])+1e-7);
    }
  }
  cout << "Tests passed!\n";
}
