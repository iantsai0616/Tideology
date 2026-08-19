/**
 * Description: Solves A*x=b. Returns {rank, x}, or {-1, {}} if inconsistent.
 * Time: O(N^2M)
 * Status: stress-tested
 */
#pragma once

typedef vector<double>vd;
const double eps = 1e-12;

pair<int, vd> solveLinear(vector<vd>A, vd b, int m = -1){
  int n = sz(A), rank = 0, br = 0, bc = 0;
  if(n) m = sz(A[0]);
  else if(m == -1) m = 0;
  vi col(m);
  iota(all(col), 0);
  rep(i, 0, n){
    double v, bv = 0;
    rep(r, i, n) rep(c, i, m) if((v = abs(A[r][c])) > bv)
      br = r, bc = c, bv = v;
    if(bv <= eps){
      rep(j, i, n) if(abs(b[j]) > eps) return {-1, {}};
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j, 0, n) swap(A[j][i], A[j][bc]);
    bv = 1 / A[i][i];
    rep(j, i + 1, n){
      double z = A[j][i] * bv;
      b[j] -= z * b[i];
      rep(k, i + 1, m) A[j][k] -= z * A[i][k];
    }
    rank++;
  }
  vd x(m);
  for(int i = rank; i--;){
    b[i] /= A[i][i];
    x[col[i]] = b[i];
    rep(j, 0, i) b[j] -= A[j][i] * b[i];
  }
  return {rank, x};
}
