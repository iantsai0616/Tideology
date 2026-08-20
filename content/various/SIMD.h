/**
 * Description: Small AVX2 helpers. Uses fixed-width types with #define int.
 * Status: x86-64 test included
 */
#pragma once

#if defined(__x86_64__) || defined(_M_X64)
#pragma GCC target("avx2")
#include <immintrin.h>

using mi = __m256i;
mi load256(const void* p){ return _mm256_loadu_si256((const mi*)p); }
mi zero256(){ return _mm256_setzero_si256(); }
mi one256(){ return _mm256_set1_epi32(-1); }
bool allZero(mi x){ return _mm256_testz_si256(x, x); }
bool allOne(mi x){ return _mm256_testc_si256(x, one256()); }
ll sumI32(mi x){
  alignas(32) int32_t v[8]; _mm256_store_si256((mi*)v, x);
  ll ans = 0; rep(i, 0, 8) ans += v[i];
  return ans;
}
ll filteredDotProduct(ll n, const int16_t* a, const int16_t* b){
  ll i = 0, ans = 0;
  mi lo = zero256(), hi = zero256();
  while(i + 16 <= n){
    mi x = load256(a + i), y = load256(b + i); i += 16;
    x = _mm256_and_si256(_mm256_cmpgt_epi16(y, x), x);
    mi z = _mm256_madd_epi16(x, y);
    lo = _mm256_add_epi64(lo,
      _mm256_cvtepi32_epi64(_mm256_castsi256_si128(z)));
    hi = _mm256_add_epi64(hi,
      _mm256_cvtepi32_epi64(_mm256_extracti128_si256(z, 1)));
  }
  alignas(32) int64_t v[4];
  _mm256_store_si256((mi*)v, _mm256_add_epi64(lo, hi));
  rep(j, 0, 4) ans += v[j];
  for(;i < n;i++) if(a[i] < b[i]) ans += a[i]*b[i];
  return ans;
}
#endif
