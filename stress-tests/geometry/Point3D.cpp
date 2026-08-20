#include "../utilities/template.h"
#include "../../content/geometry/Point3D.h"

int main(){
  using P = Point3D<double>;
  auto q = planeProj(P(0, 0, 0), P(1, 0, 0), P(0, 1, 0), P(2, 3, 5));
  assert(abs(q.F - 2) < 1e-9 && abs(q.S - 3) < 1e-9);
  cout << "Tests passed!\n";
}
