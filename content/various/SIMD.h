/**
 * Author: Simon Lindholm
 * Date: 2015-03-18
 * License: CC0
 * Source: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
 * Description: Easy SIMD with GCC vector extensions: \texttt{v32} holds W int32's (\texttt{v16}: 2W int16's).
 * Write the loop body like scalar code: scalars are broadcast, comparisons give -1/0 per lane,
 * \texttt{m ? a : b} selects per lane, \texttt{v[j]} is lane j. Try a plain loop first; use this only if
 * \texttt{-fopt-info-vec} says it did not vectorize. Below: cheat sheet of AVX2 intrinsics (x86 only) for movemask, shuffle, madd etc.
 * Names follow \texttt{"\_mm(256)?\_name\_(si(128|256)|epi(8|16|32|64)|pd|ps)"}; grep for \texttt{\_mm256\_} in
 * \texttt{/usr/lib/gcc/{*}/{*}/include/} for more. Safe to include after \texttt{\#define int long long}.
 * Status: stress-tested, also under \#define int long long
 */
#pragma once

#if defined(__x86_64__) || defined(_M_X64)
#pragma GCC target("avx2")
const int W = 8; // int32 lanes per vector (AVX2)
#else
const int W = 4; // ARM NEON, for local testing
#endif
typedef int32_t v32 __attribute__((vector_size(4 * W)));
typedef int16_t v16 __attribute__((vector_size(4 * W)));
v32 load(const int32_t* p){ v32 v; memcpy(&v, p, sizeof v); return v; }
v16 load(const int16_t* p){ v16 v; memcpy(&v, p, sizeof v); return v; }
void store(int32_t* p, v32 v){ memcpy(p, &v, sizeof v); }
void store(int16_t* p, v16 v){ memcpy(p, &v, sizeof v); }
// Usage (under #define int: array AND scalars must be int32_t,
// x > t with t a long long does not compile):
// v32 s = {}; int i = 0;
// for(; i + W <= n; i += W){ v32 x = load(a + i); s += x > t ? x : 0; }
// ll r = 0; rep(j, 0, W) r += s[j];  then a normal loop for i < n.
// Lanes stay 32/16-bit: sums can overflow, widen in time.

#if defined(__x86_64__) || defined(_M_X64)
#pragma push_macro("int") // #define int long long would break
#undef int                // the intrinsics header, so hide it
#include <immintrin.h> /** keep-include */
#pragma pop_macro("int")

using mi = __m256i; // v32 <-> mi by cast: _mm256_movemask_epi8((mi)(x == 5))

// High-level/specific methods:
// load(u)?_si256, store(u)?_si256, setzero_si256, _mm_malloc
// blendv_(epi8|ps|pd) (z?y:x), movemask_epi8 (hibits of bytes)
// i32gather_epi32(addr, x, 4): map addr[] over 32-b parts of x
// sad_epu8: sum of absolute differences of u8, outputs 4xi64
// maddubs_epi16: dot product of unsigned i7's, outputs 16xi15
// madd_epi16: dot product of signed i16's, outputs 8xi32
// extracti128_si256(x,i) (256->128), cvtsi128_si32 (128->lo32)
// permute2f128_si256(x,x,1) swaps 128-bit lanes
// shuffle_epi32(x, 3*64+2*16+1*4+0) == x for each lane
// shuffle_epi8(x, y) takes a vector instead of an imm

// Methods that work with most data types (append e.g. _epi32):
// set1, blend (i8?x:y), add, adds (sat.), mullo, sub, and/or,
// andnot, abs, min, max, sign(1,x), cmp(gt|eq), unpack(lo|hi)

// Pitfalls: cmpgt is signed only (unsigned: xor both with
// set1_epi16(0x8000) first); no 64-bit mullo; shuffle/unpack/
// alignr work inside each 128-bit half separately.
// Count: c = sub_epi16(c, cmpgt_epi16(x, y)) adds 1 where x>y;
// sumI32(madd_epi16(c, set1_epi16(1))) sums the 16 i16 lanes.

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
