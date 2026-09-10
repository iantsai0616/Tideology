#include "../utilities/template.h"

#include "../../content/numerical/MatrixInverse.h"

int main(){
  mt19937 rng(123);
  rep(n, 1, 20) rep(it, 0, 300){
    vector<vector<double>> a(n, vector<double>(n));
    rep(i, 0, n) a[i][i] = 1;
    rep(q, 0, 5*n){
      int x = rng()%n, y = rng()%n;
      if(x == y) continue;
      double c = (int)(rng()%7)-3;
      rep(j, 0, n) a[x][j] += c*a[y][j];
    }
    auto orig = a;
    assert(matInv(a) == n);
    rep(i, 0, n) rep(j, 0, n){
      double sum = 0;
      rep(k, 0, n) sum += orig[i][k]*a[k][j];
      assert(abs(sum-(i == j)) < 1e-7);
    }
  }
  vector<vector<double>> singular = {{1, 2}, {2, 4}};
  assert(matInv(singular) == 1);
  cout << "Tests passed!\n";
}
