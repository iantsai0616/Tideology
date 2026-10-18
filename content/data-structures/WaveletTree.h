/**
 * Author: Benjamin Qi
 * Source: https://github.com/bqi343/cp-notebook (Wavelet.h); cnt added
 * License: CC0
 * Description: Static range queries on values in $[0, SZ)$, SZ a power of two
 * (coordinate-compress first). Declare globally.
 * query(l, r, k): k-th smallest (1-indexed) in a[l, r); cnt(l, r, x): \#a[i] < x in [l, r).
 * Time: $O(N \log SZ)$ build and memory, $O(\log SZ)$ per query
 * Status: stress-tested, Library Checker range\_kth\_smallest
 */
#pragma once

template<int SZ> struct Wavelet {
  vector<int32_t> nl[SZ]; // nl[x][i] = # of the first i going left
  void build(const vi& a, int x = 1, int L = 0, int R = SZ - 1){
    if(L == R) return;
    nl[x] = {0};
    vi A[2]; int M = (L + R) / 2;
    for(int t : a) A[t > M].pb(t), nl[x].pb(sz(A[0]));
    build(A[0], 2*x, L, M), build(A[1], 2*x+1, M + 1, R);
  }
  int query(int lo, int hi, int k, int x = 1, int L = 0, int R = SZ - 1){
    if(L == R) return L;
    int M = (L + R) / 2, t = nl[x][hi] - nl[x][lo];
    if(t >= k) return query(nl[x][lo], nl[x][hi], k, 2*x, L, M);
    return query(lo - nl[x][lo], hi - nl[x][hi], k - t, 2*x+1, M + 1, R);
  }
  int cnt(int lo, int hi, int v, int x = 1, int L = 0, int R = SZ - 1){
    if(lo == hi || v <= L) return 0;
    if(R < v) return hi - lo;
    int M = (L + R) / 2;
    return cnt(nl[x][lo], nl[x][hi], v, 2*x, L, M)
      + cnt(lo - nl[x][lo], hi - nl[x][hi], v, 2*x+1, M + 1, R);
  }
};
