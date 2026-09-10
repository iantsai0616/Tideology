/**
 * Description: Solves A*x=b. Undetermined x[i] are NaN.
 * Returns {rank, x}, or {-1, {}} if inconsistent.
 * Time: O(NM min(N, M))
 * Status: stress-tested
 */
#pragma once

#include "SolveLinear.h"

pair<int, vd> solveLinear2(vector<vd>A, vd b, int m = -1){
  int n = sz(A), r = 0;
  if(n) m = sz(A[0]);
  else if(m == -1) m = 0;
  vi col;
  rep(c, 0, m){
    if(r == n) break;
    int p = r;
    rep(i, r, n) if(abs(A[i][c]) > abs(A[p][c])) p = i;
    if(abs(A[p][c]) <= eps) continue;
    swap(A[p], A[r]);
    swap(b[p], b[r]);
    double z = A[r][c];
    rep(j, c, m) A[r][j] /= z;
    b[r] /= z;
    rep(i, 0, n) if(i != r){
      z = A[i][c];
      rep(j, c, m) A[i][j] -= z * A[r][j];
      b[i] -= z * b[r];
    }
    col.pb(c);
    r++;
  }
  rep(i, r, n) if(abs(b[i]) > eps) return {-1, {}};
  vd x(m, numeric_limits<double>::quiet_NaN());
  vector<bool>pivot(m);
  for(int c : col) pivot[c] = 1;
  rep(i, 0, r){
    bool unique = 1;
    rep(c, 0, m) if(!pivot[c] and abs(A[i][c]) > eps) unique = 0;
    if(unique) x[col[i]] = b[i];
  }
  return {r, x};
}
