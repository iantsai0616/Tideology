#include "../utilities/template.h"
#include "../../content/geometry/PolarAngleComp.h"

int main(){
  vector<P> p = {P(-1, 0), P(0, -1), P(0, 1), P(2, 0), P(1, 0)};
  sort(all(p), [](P a, P b){ return polarCmp(a, b); });
  vector<P> ans = {P(1, 0), P(2, 0), P(0, 1), P(-1, 0), P(0, -1)};
  assert(p == ans);
  assert(polarCmp(P(1, 1), P(2, 2), false) == -1);
  cout << "Tests passed!\n";
}
