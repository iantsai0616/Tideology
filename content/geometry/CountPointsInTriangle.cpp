/**
 * Author: Tideology
 * Source: inclusion-exclusion over "points below a segment"; ties in x are broken by y,
 * which is a shear and keeps every orientation, so vertical edges need no special case.
 * Description: Number of points of B strictly inside triangle A[a], A[b], A[c]
 * (points on the border or equal to a vertex do not count). A = B is fine.
 * Usage: TriCount tc(A, B); tc.query(a, b, c);
 * Time: O(N^2 M) preprocessing, O(1) per query
 * Status: stress-tested, Library Checker count\_points\_in\_triangle
 */
struct TriCount {
  vector<pll> A, B; vector<vector<int32_t>> lo, on; vi eq;
  TriCount(const vector<pll>& a, vector<pll> b) : A(a), B(b),
      lo(sz(a), vector<int32_t>(sz(a))), on(lo), eq(sz(a)) {
    sort(all(B));
    rep(i, 0, sz(A)){
      int s = upper_bound(all(B), A[i]) - B.begin();
      eq[i] = s - (lower_bound(all(B), A[i]) - B.begin());
      rep(j, 0, sz(A)) if(A[i] < A[j])
        for(int k = s; k < sz(B) && B[k] < A[j]; k++){
          int o = ori(A[i], A[j], B[k]); // lo: strictly below, on: on the open segment
          lo[i][j] += o < 0, on[i][j] += o == 0;
        }
    }
  }
  int query(int a, int b, int c){
    if(A[b] < A[a]) swap(a, b);
    if(A[c] < A[b]) swap(b, c);
    if(A[b] < A[a]) swap(a, b);
    int o = ori(A[a], A[c], A[b]);
    if(o > 0) return lo[a][b] + lo[b][c] - lo[a][c] - on[a][c];
    if(o < 0) return lo[a][c] - lo[a][b] - on[a][b] - lo[b][c] - on[b][c] - eq[b];
    return 0;
  }
};
