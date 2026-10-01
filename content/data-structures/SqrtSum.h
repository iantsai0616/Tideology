/**
 * Description: Sqrt decomposition: point add and range sum on [0, n).
 * Pair with Mo (many adds, few queries), e.g. on the value domain.
 * kth: min p with sum [0, p] > k, needs all a >= 0; n if none.
 * Usage: SqrtSum s(n); s.add(i, v); s.query(l, r) = sum [l, r); s.kth(k);
 * Time: O(1) add, O(\sqrt N) query/kth
 * Status: stress-tested
 */
#pragma once

struct SqrtSum {
  int n, B; vector<ll> a, blk;
  SqrtSum(int n) : n(n), B((int)sqrt(n)+1), a(n), blk(n/B+1){}
  void add(int i, ll v){ a[i]+=v, blk[i/B]+=v; } // a[i] += v
  ll query(int l, int r){
    ll s=0;
    for(; l<r and l%B; l++) s+=a[l];
    for(; l+B<=r; l+=B) s+=blk[l/B];
    for(; l<r; l++) s+=a[l];
    return s;
  }
  int kth(ll k){
    int b=0, i;
    for(; b<sz(blk) and blk[b]<=k; b++) k-=blk[b];
    for(i=b*B; i<n and a[i]<=k; i++) k-=a[i];
    return min(i, n);
  }
};
