#include "../utilities/template.h"
#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/MinkowskiSum.h"

int main(){
  rep(it, 0, 5000){
    vector<P> a, b;
    rep(i, 0, rand() % 8 + 1) a.pb(P(rand() % 11 - 5, rand() % 11 - 5));
    rep(i, 0, rand() % 8 + 1) b.pb(P(rand() % 11 - 5, rand() % 11 - 5));
    a = convexHull(a); b = convexHull(b);
    vector<P> brute;
    for(P x : a) for(P y : b) brute.pb(x + y);
    brute = convexHull(brute);
    vector<P> ans = convexHull(minkowski(a, b));
    sort(all(ans)); sort(all(brute));
    assert(ans == brute);
  }
  cout << "Tests passed!\n";
}
