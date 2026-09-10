#include "../utilities/template.h"
#include "../../content/geometry/HPIGeneralLine.h"

long double area(const vector<DP>& p){
  long double ans = 0;
  rep(i, 0, sz(p)) ans += p[i].cross(p[(i + 1) % sz(p)]);
  return abs(ans) / 2;
}
int main(){
  vector<IHalfPlane> h = {{-1, 0, 0}, {1, 0, -1},
                          {0, -1, 0}, {0, 1, -1}};
  auto p = integerHalfPlaneIntersection(h, 10);
  assert(sz(p) == 4 && abs(area(p) - 1) < 1e-12);
  h.pb({0, -1, 2});
  assert(integerHalfPlaneIntersection(h, 10).empty());
  cout << "Tests passed!\n";
}
