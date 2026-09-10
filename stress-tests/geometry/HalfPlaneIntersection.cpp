#include "../utilities/template.h"
#include "../../content/geometry/HalfPlaneIntersection.h"

double area(const vector<P>& p){
  double ans = 0;
  rep(i, 0, sz(p)) ans += p[i].cross(p[(i + 1) % sz(p)]);
  return abs(ans) / 2;
}
int main(){
  vector<HalfPlane> h = {
    {P(0, 0), P(1, 0)}, {P(1, 0), P(1, 1)},
    {P(1, 1), P(0, 1)}, {P(0, 1), P(0, 0)}
  };
  auto p = halfPlaneIntersection(h, 10);
  assert(sz(p) == 4 && abs(area(p) - 1) < 1e-9);
  h.pb({P(0, 2), P(1, 2)});
  assert(halfPlaneIntersection(h, 10).empty());
  cout << "Tests passed!\n";
}
