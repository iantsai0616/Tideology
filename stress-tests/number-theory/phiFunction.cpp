#include "../utilities/template.h"

#include "../../content/number-theory/phiFunction.h"

int main(){
  auto st = chrono::steady_clock::now();
  calculatePhi();
  double sec = chrono::duration<double>(chrono::steady_clock::now()-st).count();
  rep(n, 1, 5000){
    int ans = 0;
    rep(i, 1, n+1) ans += gcd(i, n) == 1;
    assert(phi[n] == ans);
  }
  assert(phi[1] == 1 && phi[36] == 12 && phi[4999999] == 4999998);
  assert(sec < 2);
  cout << "Tests passed! " << sec << "s\n";
}
