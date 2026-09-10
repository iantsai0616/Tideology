#include "../utilities/template.h"
#include "../../content/numerical/SolveLinear.h"

int getRank(vector<vd>A){
  int n = sz(A), m = n ? sz(A[0]) : 0, r = 0;
  rep(c, 0, m){
    if(r == n) break;
    int p = r;
    rep(i, r, n) if(abs(A[i][c]) > abs(A[p][c])) p = i;
    if(abs(A[p][c]) < 1e-9) continue;
    swap(A[p], A[r]);
    rep(i, r + 1, n){
      double z = A[i][c] / A[r][c];
      rep(j, c, m) A[i][j] -= z * A[r][j];
    }
    r++;
  }
  return r;
}
int main(){
  mt19937 rng(3);
  rep(it, 0, 20000){
    int n = rng() % 8, m = rng() % 8;
    vector<vd>A(n, vd(m));
    vd b(n);
    rep(i, 0, n) rep(j, 0, m) A[i][j] = (int)(rng() % 11) - 5;
    rep(i, 0, n) b[i] = (int)(rng() % 11) - 5;
    vector<vd>aug = A;
    rep(i, 0, n) aug[i].pb(b[i]);
    int rank = getRank(A), rankAug = getRank(aug);
    auto [gotRank, x] = solveLinear(A, b, m);
    if(rank != rankAug) assert(gotRank == -1 and x.empty());
    else{
      assert(gotRank == rank and sz(x) == m);
      rep(i, 0, n){
        double sum = 0;
        rep(j, 0, m) sum += A[i][j] * x[j];
        assert(abs(sum - b[i]) < 1e-7);
      }
    }
  }
  cout << "Tests passed!\n";
}
