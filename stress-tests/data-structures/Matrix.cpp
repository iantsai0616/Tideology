#include "../utilities/template.h"

#include "../../content/data-structures/Matrix.h"

int main(){
  Matrix<ll, 2> a; a.d = {{{{1, 1}}, {{1, 0}}}};
  array<ll, 2> v = {1, 0};
  vector<ll> fib = {0, 1};
  rep(i, 2, 45) fib.pb(fib[i-1] + fib[i-2]);
  rep(k, 0, 40){
    auto r = (a^k)*v;
    assert(r[0] == fib[k+1] && r[1] == fib[k]);
  }
  Matrix<ll, 3> id;
  rep(i, 0, 3) id.d[i][i] = 1;
  Matrix<ll, 3> b; int z = 0;
  rep(i, 0, 3) rep(j, 0, 3) b.d[i][j] = ++z;
  assert((b*id).d == b.d && (id*b).d == b.d);
  cout << "Tests passed!\n";
}
