#include "../utilities/template.h"
#include "../../content/number-theory/ModMulLL.h"

int main(){
  mt19937_64 rng(1);
  rep(it, 0, 2000000){
    ull m=rng()|1, a=rng()%m, b=rng()%m;
    assert(modmul(a, b, m)==(ull)((__uint128_t)a*b%m));
  }
  for(ull m:{1ULL, 2ULL, 998244353ULL, ULLONG_MAX})
    for(ull a:{0ULL, 1ULL, m-1}) for(ull b:{0ULL, 1ULL, m-1})
      assert(modmul(a%m, b%m, m)==(ull)((__uint128_t)(a%m)*(b%m)%m));
  assert(modpow(2, 63, 1000000007)==291172004);
  cout<<"Tests passed!\n";
}
