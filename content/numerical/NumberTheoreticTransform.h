/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
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
const int N = (1<<20); // change if necessary, has to be 2^k
const ll mod = 998244353, G = 3;
ll mul(ll a, ll b){ return a * b % mod; }
ll add(ll a, ll b){ return a + b < mod ? a + b : a + b - mod; }
ll sub(ll a, ll b){ return a < b ? a - b + mod : a - b; }
ll Pow(ll a, ll e){ ll r = 1; for(; e; e >>= 1, a = mul(a, a)) if(e & 1) r = mul(r, a); return r; }

struct NTT {
  ll w[N];
  NTT() { // w[k + j] = (2k-th root)^j
    for (int k = 1; k < N; k <<= 1) {
      ll dw = Pow(G, (mod - 1) / (2 * k)); w[k] = 1;
      for (int j = 1; j < k; ++j) w[k + j] = mul(w[k + j - 1], dw);
    }
  } // 0 <= a[i] < P
  void operator()(vector<ll>& a, bool inv = false) {
    int n = sz(a);
    for (int j = 1, x = 0; j < n - 1; ++j) {
      for (int k = n >> 1; (x ^= k) < k; k >>= 1);
      if (j < x) swap(a[x], a[j]);
    }
    for (int L = 2; L <= n; L <<= 1) {
      int dl = L >> 1;
      for (int i = 0; i < n; i += L) {
        for (int j = i, x = dl; j < i + dl; ++j, ++x) {
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
