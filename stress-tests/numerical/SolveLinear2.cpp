#include "../utilities/template.h"
#include "../../content/numerical/SolveLinear2.h"

int main(){
  vector<vd>A{{1, 1, 0}, {0, 0, 1}};
  vd b{3, 4};
  auto [rank, x] = solveLinear2(A, b);
  assert(rank == 2);
  assert(isnan(x[0]) and isnan(x[1]) and abs(x[2] - 4) < eps);
  A = {{1, 2}, {2, 4}};
  b = {3, 7};
  tie(rank, x) = solveLinear2(A, b);
  assert(rank == -1 and x.empty());
  mt19937 rng(1);
  rep(it, 0, 1000){
    int n = rng() % 8 + 1;
    vector<vd>M(n, vd(n));
    vd want(n), rhs(n);
    for(double &v : want) v = (int)(rng() % 21) - 10;
    rep(i, 0, n) rep(j, 0, n) M[i][j] = (int)(rng() % 21) - 10;
    rep(i, 0, n) rep(j, 0, n) rhs[i] += M[i][j] * want[j];
    tie(rank, x) = solveLinear2(M, rhs);
    assert(rank != -1);
    rep(i, 0, n) if(!isnan(x[i])) assert(abs(x[i] - want[i]) < 1e-7);
  }
  cout << "Tests passed!\n";
}
