#include "../utilities/template.h"
#include "../../content/geometry/PointInCircle.h"

int main(){
  array<P, 3> p = {P(0, 0), P(4, 0), P(0, 3)};
  assert(inCircle(p, P(2, 1)));
  assert(!inCircle(p, P(4, 0)));
  assert(!inCircle(p, P(5, 5)));
  swap(p[1], p[2]);
  assert(inCircle(p, P(2, 1)));
  cout << "Tests passed!\n";
}
