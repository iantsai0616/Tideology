#include "../utilities/template.h"
#include "../../content/geometry/VoronoiDiagram.h"

long double area(const vector<DP>& p){
  long double ans = 0;
  rep(i, 0, sz(p)) ans += p[i].cross(p[(i + 1) % sz(p)]);
  return abs(ans) / 2;
}
int main(){
  vector<P> p = {P(0, 0), P(4, 0), P(0, 3), P(6, 5)};
  VoronoiDiagram tool(p);
  long double sum = 0;
  rep(i, 0, sz(p)){
    auto cell = tool.polygon(i, 100);
    assert(!cell.empty()); sum += area(cell);
    for(DP q : cell) rep(j, 0, sz(p)){
      auto d = [&](P x){
        return (q.x - x.x)*(q.x - x.x) + (q.y - x.y)*(q.y - x.y);
      };
      assert(d(p[i]) <= d(p[j]) + 1e-7);
    }
  }
  assert(abs(sum - 40000) < 1e-7);
  cout << "Tests passed!\n";
}
