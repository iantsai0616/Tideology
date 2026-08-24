#include "../utilities/template.h"

#include "../../content/numerical/PolyInterpolate.h"
#include "../../content/numerical/Polynomial.h"
#include "../../content/numerical/PolyRoots.h"

bool eq(double a, double b){ return abs(a-b) < 1e-7; }

int main(){
  Poly p{{-2, -1, 1}};
  assert(eq(p(2), 0) && eq(p(-1), 0));
  Poly q = p; q.diff();
  assert(sz(q.a) == 2 && eq(q.a[0], -1) && eq(q.a[1], 2));
  q = p; q.divroot(2);
  assert(sz(q.a) == 2 && eq(q.a[0], 1) && eq(q.a[1], 1));
  mt19937 rng(123);
  rep(n, 1, 15) rep(it, 0, 1000){
    vd coef(n), x(n), y(n);
    for(double &v : coef) v = (int)(rng()%11)-5;
    Poly f{coef};
    rep(i, 0, n) x[i] = i-n/2.0, y[i] = f(x[i]);
    auto got = interpolate(x, y, n);
    rep(i, 0, n) assert(eq(got[i], coef[i]));
  }
  auto roots = polyRoots(Poly{{0, 0, 1}}, -1, 1);
  assert(sz(roots) == 1 && eq(roots[0], 0));
  roots = polyRoots(Poly{{-10, 1}}, -1, 1);
  assert(roots.empty());
  roots = polyRoots(Poly{{2, -3, 0, 1}}, -10, 10);
  sort(all(roots));
  assert(sz(roots) == 2 && eq(roots[0], -2) && eq(roots[1], 1));
  cout << "Tests passed!\n";
}
