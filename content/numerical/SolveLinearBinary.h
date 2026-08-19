/**
 * Description: Solves A*x=b over F2. Returns {rank, x}, or {-1, {}}.
 * Time: O(N^2M)
 * Status: stress-tested
 */
#pragma once

typedef bitset<1000>bs;

pair<int, bs> solveLinear(vector<bs>A, vi b, int m){
  int n = sz(A), rank = 0, br;
  assert(m <= sz(bs()));
  vi col(m);
  iota(all(col), 0);
  rep(i, 0, n){
    for(br = i; br < n; br++) if(A[br].any()) break;
    if(br == n){
      rep(j, i, n) if(b[j]) return {-1, {}};
      break;
    }
    int bc = A[br]._Find_next(i - 1);
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j, 0, n) if(A[j][i] != A[j][bc]) A[j].flip(i), A[j].flip(bc);
    rep(j, i + 1, n) if(A[j][i]) b[j] ^= b[i], A[j] ^= A[i];
    rank++;
  }
  bs x;
  for(int i = rank; i--;){
    if(!b[i]) continue;
    x[col[i]] = 1;
    rep(j, 0, i) b[j] ^= A[j][i];
  }
  return {rank, x};
}
