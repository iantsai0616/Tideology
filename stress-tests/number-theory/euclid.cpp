#include "../utilities/template.h"

#include "../../content/number-theory/euclid.h"

int main(){
  mt19937_64 rng(123);
  rep(it, 0, 1000000){
    ll a = rng()%1000000000000LL, b = rng()%1000000000000LL, x, y;
    ll d = euclid(a, b, x, y);
    assert(d == gcd(a, b));
    assert((__int128)a*x + (__int128)b*y == d);
  }
  cout << "Tests passed!\n";
}
