#include "../utilities/template.h"
#include "../../content/geometry/CalcPointsInTriangle.h"

int main(){
  rep(it, 0, 200){
    int n = rand() % 8 + 1, m = rand() % 8 + 1;
    vector<P> a(n), b(m);
    for(P& p : a) p = P(rand() % 11 - 5, rand() % 11 - 5);
    for(P& p : b) p = P(rand() % 11 - 5, rand() % 11 - 5);
    PointsInTriangle tool(a, b);
    rep(i, 0, n) rep(j, 0, n) rep(k, 0, n){
      int ans = 0;
      for(P p : b){
        ll x = a[i].cross(a[j], p), y = a[j].cross(a[k], p);
        ll z = a[k].cross(a[i], p);
        ans += (x > 0 && y > 0 && z > 0) ||
               (x < 0 && y < 0 && z < 0);
      }
      assert(tool.query(i, j, k) == ans);
    }
  }
  cout << "Tests passed!\n";
}
