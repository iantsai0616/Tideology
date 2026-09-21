#include "../utilities/template.h"
#ifdef TEST_WIDE
#define int long long
#endif
#include "../../content/numerical/NumberTheoreticTransform.h"

vl naive(const vl &a, const vl &b){
  if(a.empty() or b.empty()) return {};
  vl c(sz(a) + sz(b) - 1);
  rep(i, 0, sz(a)) rep(j, 0, sz(b)){
    c[i + j] = (c[i + j] + a[i] * b[j]) % ntt_mod;
  }
  return c;
}
signed main(signed argc, char**){
  mt19937 rng(1);
  auto check = [&](int n, int m){
    vl a(n), b(m);
    for(ll &x : a) x = rng() % ntt_mod;
    for(ll &x : b) x = rng() % ntt_mod;
    vl a0 = a, b0 = b;
    assert(conv(a, b) == naive(a, b));
    assert(a == a0 and b == b0);
  };
  vector<int> sizes{0, 1, 2, 59, 60, 61, 63, 64, 65, 127, 128, 129, 257};
  for(int n : sizes) for(int m : sizes) check(n, m);
  rep(it, 0, 3000) check(rng() % 320, rng() % 320);
  for(int n : {1, 2, 4, 16, 128, 8, 256, 32}){
    vl a(n);
    for(ll &x : a) x = rng() % ntt_mod;
    vl b = a;
    ntt(b);
    rep(k, 0, n){
      ll sum = 0;
      rep(i, 0, n){
        sum = (sum + a[i] * nttPow(ntt_root, k * i * (ntt_mod - 1) / n)) % ntt_mod;
      }
      assert(sum == b[k]);
    }
  }
  for(ll value : {0LL, 1LL, ntt_mod - 1}){
    vl a(257, value), b(129, value);
    assert(conv(a, b) == naive(a, b));
    assert(conv(a, a) == naive(a, a));
  }
  int n = argc > 1 ? (1 << 22) : (1 << 18), m = 61;
  vl a(n, 1), b(m, 1), c = conv(a, b);
  assert(sz(c) == n + m - 1);
  rep(i, 0, sz(c)) assert(c[i] == min({i + 1, m, n + m - 1 - i}));
  cout << "Tests passed!\n";
}
