/**
 * Source: Cached roots, DIF/DIT convolution
 * Description: NTT/convolution mod 998244353; inputs in $[0, mod)$, size up to $2^{23}$.
 * Time: O(N log N)
 * Status: stress-tested and benchmarked
 * //(2^16)+1, 65537, 3
 * 7*17*(2^23)+1, 998244353, 3
 * 1255*(2^20)+1, 1315962881, 3
 * 51*(2^25)+1, 1711276033, 29
 * only works when sz(A) + sz(B) - 1 <= N
 */
#pragma once
// mul, add, sub, Pow for long long integers need to add
const int N = (1<<20); // change if necessary, has to be 2^k
const ll mod = 998244353, G = 3;

struct NTT {
  ll w[N];
  NTT() {
    ll dw = Pow(G, (mod - 1) / N);
    w[0] = 1;
    for (int i = 1; i < N; ++i)
      w[i] = mul(w[i - 1], dw);
  } // 0 <= a[i] < P
  void operator()(vector<ll>& a, bool inv = false) {
    int n = sz(a);
    for (int j = 1, x = 0; j < n - 1; ++j) {
      for (int k = n >> 1; (x ^= k) < k; k >>= 1);
      if (j < x) swap(a[x], a[j]);
    }
    for (int L = 2; L <= n; L <<= 1) {
      int dx = N / L, dl = L >> 1;
      for (int i = 0; i < n; i += L) {
        for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
          ll tmp = mul(a[j + dl], w[x]);
          a[j + dl] = sub(a[j], tmp);
          a[j] = add(a[j], tmp);
        }
      }
    }
    if (inv) {
      reverse(1 + all(a));
      ll invn = Pow(n, mod - 2);
      for (int i = 0; i < n; ++i)
        a[i] = mul(a[i], invn);
    }
  }
} ntt;
