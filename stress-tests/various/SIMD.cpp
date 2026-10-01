#include <cassert> // GCC 16: bits/stdc++.h no longer includes it
#include "../utilities/template.h"
#define int long long // same as the contest template
#include "../../content/various/SIMD.h"
static_assert(sizeof(int) == 8, "SIMD.h must keep #define int");

signed main(){
  mt19937 rng(2);
  rep(it, 0, 3000){ // vector extensions (all architectures)
    ll n = rng() % 100;
    int32_t a[100], c[100]; int16_t s[100];
    int32_t t = int32_t(rng() % 2000) - 1000;
    rep(i, 0, n) a[i] = int32_t(rng() % 2000) - 1000, s[i] = int16_t(a[i]);

    v32 sum = {}, cnt = {}, mx = v32{} - 1001; // scalar broadcast
    ll i = 0;
    for(; i + W <= n; i += W){
      v32 x = load(a + i);
      sum += x > t ? x : 0; // per-lane select
      cnt -= x == t;        // comparison gives -1 / 0
      mx = x > mx ? x : mx;
      store(c + i, x * 3 - 1);
    }
    ll got = 0, gotCnt = 0; int32_t gotMx = -1001;
    rep(j, 0, W) got += sum[j], gotCnt += cnt[j], gotMx = max(gotMx, mx[j]);
    for(; i < n; i++)
      got += a[i] > t ? a[i] : 0, gotCnt += a[i] == t, gotMx = max(gotMx, a[i]), c[i] = a[i] * 3 - 1;
    ll want = 0, wantCnt = 0; int32_t wantMx = -1001;
    rep(j, 0, n) want += a[j] > t ? a[j] : 0, wantCnt += a[j] == t, wantMx = max(wantMx, a[j]);
    assert(got == want && gotCnt == wantCnt && gotMx == wantMx);
    rep(j, 0, n) assert(c[j] == a[j] * 3 - 1);

    v16 c16 = {}; ll k = 0, got16 = 0, want16 = 0;
    for(; k + 2 * W <= n; k += 2 * W) c16 -= load(s + k) > (int16_t)t;
    rep(j, 0, 2 * W) got16 += c16[j];
    for(; k < n; k++) got16 += s[k] > t;
    rep(j, 0, n) want16 += s[j] > t;
    assert(got16 == want16);
  }

#if defined(__x86_64__) || defined(_M_X64)
  rep(it, 0, 3000){ // v32 -> mi cast, as in the cheat sheet comment
    int32_t a[8]; rep(i, 0, 8) a[i] = int32_t(rng() % 3) + 4;
    ll want = 0; rep(i, 0, 8) want += a[i] == 5;
    v32 x = load(a);
    assert(__builtin_popcount((unsigned)_mm256_movemask_epi8((mi)(x == 5))) == 4 * want);
  }

  alignas(32) int16_t a[16], b[16];
  rep(i, 0, 16) a[i] = int16_t(i - 8), b[i] = int16_t(10 - i);
  ll ans = 0;
  rep(i, 0, 16) if(a[i] < b[i]) ans += a[i]*b[i];
  assert(filteredDotProduct(16, a, b) == ans);

  rep(it, 0, 3000){ // random lengths: full range, only extremes, small values
    ll n = rng() % 100;
    int16_t x[100], y[100];
    rep(i, 0, n){
      if(it % 3 == 0) x[i] = int16_t(rng()), y[i] = int16_t(rng());
      else if(it % 3 == 1)
        x[i] = int16_t(rng() & 1 ? INT16_MIN : INT16_MAX),
        y[i] = int16_t(rng() & 1 ? INT16_MIN : INT16_MAX);
      else x[i] = int16_t((ll)(rng() % 7) - 3), y[i] = int16_t((ll)(rng() % 7) - 3);
    }
    ll want = 0;
    rep(i, 0, n) if(x[i] < y[i]) want += x[i]*y[i];
    assert(filteredDotProduct(n, x, y) == want);
  }

  rep(it, 0, 3000){ // sumI32, allZero, allOne
    int32_t v[8];
    int32_t c = it & 1 ? -1 : 0; // mostly all-0 / all-1 vectors, some random
    rep(i, 0, 8) v[i] = it % 3 ? c : int32_t(rng());
    if(it % 3 == 1) v[rng() % 8] = ~c;
    ll s = 0; bool z = true, o = true;
    rep(i, 0, 8) s += v[i], z &= v[i] == 0, o &= v[i] == -1;
    mi m = load256(v);
    assert(sumI32(m) == s && allZero(m) == z && allOne(m) == o);
  }

  rep(it, 0, 3000){ // cheat-sheet idioms: counting with cmpgt, unsigned compare
    uint16_t x[16], y[16];
    rep(i, 0, 16) x[i] = uint16_t(rng()), y[i] = uint16_t(rng() % 4 ? rng() : x[i]);
    ll gt = 0, ugt = 0;
    rep(i, 0, 16) gt += (int16_t)x[i] > (int16_t)y[i], ugt += x[i] > y[i];
    mi vx = load256(x), vy = load256(y), cnt = zero256();
    rep(r, 0, 3) cnt = _mm256_sub_epi16(cnt, _mm256_cmpgt_epi16(vx, vy));
    assert(sumI32(_mm256_madd_epi16(cnt, _mm256_set1_epi16(1))) == 3 * gt);
    mi f = _mm256_set1_epi16(INT16_MIN); // 0x8000
    mi u = _mm256_cmpgt_epi16(_mm256_xor_si256(vx, f), _mm256_xor_si256(vy, f));
    assert(__builtin_popcount((unsigned)_mm256_movemask_epi8(u)) == 2 * ugt);
  }
#endif
  cout << "Tests passed!\n";
}
