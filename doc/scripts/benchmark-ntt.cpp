// Compile with -DNTT_BASELINE='"/path/to/old.h"'; optionally -DTEST_WIDE.
// Run: ./benchmark-ntt length [order]. Times are milliseconds per convolution.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)(x).size()
#ifdef TEST_WIDE
#define int long long
#endif
namespace baseline {
#include NTT_BASELINE
}
namespace candidate {
#include "../../content/numerical/NumberTheoreticTransform.h"
}
signed main(signed argc, char **argv){
  assert(argc >= 2);
  int n = stoll(argv[1]), order = argc > 2 ? stoll(argv[2]) % 2 : 0;
  mt19937 rng(1);
  vector<ll> a(n), b(n), expected;
  for(ll &x : a) x = rng() % 998244353;
  for(ll &x : b) x = rng() % 998244353;
  using Fn = vector<ll> (*)(const vector<ll>&, const vector<ll>&);
  Fn funcs[]{baseline::conv, candidate::conv};
  double cold[2];
  for(int step = 0; step < 2; step++){
    int id = (order + step) % 2;
    auto start = chrono::steady_clock::now();
    auto c = funcs[id](a, b);
    cold[id] = chrono::duration<double, milli>(chrono::steady_clock::now() - start).count();
    if(step == 0) expected = c;
    else assert(c == expected);
  }
  vector<double> samples[2];
  int repeats = max(1LL, 65536LL / n);
  for(int round = 0; round < 9; round++){
    for(int step = 0; step < 2; step++){
      int id = (order + round + step) % 2;
      auto start = chrono::steady_clock::now();
      for(int it = 0; it < repeats; it++){
        auto c = funcs[id](a, b);
        asm volatile("" : : "g"(c.data()) : "memory");
      }
      samples[id].push_back(chrono::duration<double, milli>(
          chrono::steady_clock::now() - start).count() / repeats);
    }
  }
  cout << n;
  for(int id = 0; id < 2; id++){
    sort(samples[id].begin(), samples[id].end());
    cout << ' ' << cold[id] << ' ' << samples[id][samples[id].size() / 2];
  }
  cout << '\n';
}
