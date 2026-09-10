#include "../utilities/template.h"
#include "../../content/numerical/Simplex.h"

int main(){
  {
    vvd A{{1, 1}, {1, 0}, {0, 1}};
    vd b{4, 2, 3}, c{3, 2};
    auto [val, x] = LPSolver(A, b, c).solve();
    assert(abs(val - 10) < 1e-7 and abs(x[0] - 2) < 1e-7 and abs(x[1] - 2) < 1e-7);
  }
  {
    vvd A{{1}, {-1}};
    vd b{0, -1}, c{1};
    auto [val, x] = LPSolver(A, b, c).solve();
    assert(val == -inf and x.empty());
  }
  {
    vvd A{{-1}};
    vd b{0}, c{1};
    auto [val, x] = LPSolver(A, b, c).solve();
    assert(val == inf);
  }
  mt19937 rng(5);
  rep(it, 0, 10000){
    double bx = rng() % 20 + 1, by = rng() % 20 + 1;
    vvd A{{1, 0}, {0, 1}};
    vd b{bx, by}, c{(double)(rng() % 11), (double)(rng() % 11)};
    rep(i, 0, 5){
      double x = rng() % 11, y = rng() % 11;
      A.pb({x, y});
      b.pb(x * bx + y * by + rng() % 11);
    }
    auto [val, x] = LPSolver(A, b, c).solve();
    assert(abs(val - c[0] * bx - c[1] * by) < 1e-7);
    assert(abs(x[0] - bx) < 1e-7 or c[0] == 0);
    assert(abs(x[1] - by) < 1e-7 or c[1] == 0);
  }
  cout << "Tests passed!\n";
}
