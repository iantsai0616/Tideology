#include "../utilities/template.h"
#include "../../content/numerical/SolveLinearBinary.h"

int main(){
  mt19937 rng(4);
  rep(it, 0, 30000){
    int n = rng() % 8, m = rng() % 8;
    vector<bs>A(n);
    vi b(n);
    rep(i, 0, n){
      rep(j, 0, m) A[i][j] = rng() & 1;
      b[i] = rng() & 1;
    }
    int sols = 0;
    bs want;
    rep(msk, 0, 1 << m){
      bool ok = 1;
      rep(i, 0, n){
        int sum = 0;
        rep(j, 0, m) sum ^= A[i][j] & (msk >> j & 1);
        if(sum != b[i]) ok = 0;
      }
      if(ok) sols++, want = bs(msk);
    }
    auto [rank, x] = solveLinear(A, b, m);
    if(!sols) assert(rank == -1);
    else{
      assert(rank <= m and sols == (1 << (m - rank)));
      rep(i, 0, n){
        int sum = 0;
        rep(j, 0, m) sum ^= A[i][j] & x[j];
        assert(sum == b[i]);
      }
      if(sols == 1) assert(x == want);
    }
  }
  cout << "Tests passed!\n";
}
