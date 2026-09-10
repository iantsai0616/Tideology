#include "../utilities/template.h"
#include "../../content/geometry/Heart.h"

int main(){
  P a(0, 0), b(4, 0), c(0, 3);
  auto eq = [](P p, P q){ return (p - q).dist() < 1e-9; };
  assert(eq(circumcenter(a, b, c), P(2, 1.5)));
  assert(eq(incenter(a, b, c), P(1, 1)));
  assert(eq(centroid(a, b, c), P(4.0 / 3, 1)));
  assert(eq(orthocenter(a, b, c), a));
  cout << "Tests passed!\n";
}
