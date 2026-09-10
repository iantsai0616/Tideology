#include "../utilities/template.h"
#include "../../content/geometry/VectorInPoly.h"

int main(){
  P o(0, 0);
  assert(inCone(P(0, 1), o, P(1, 0), P(1, 1), true));
  assert(!inCone(P(0, 1), o, P(1, 0), P(-1, 1), false));
  assert(!inCone(P(0, 1), o, P(1, 0), P(1, 0), true));
  assert(inCone(P(1, 0), o, P(0, 1), P(-1, -1), true));
  assert(!inCone(P(1, 0), o, P(0, 1), P(1, 1), true));
  cout << "Tests passed!\n";
}
