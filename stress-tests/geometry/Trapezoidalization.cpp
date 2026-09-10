#include "../utilities/template.h"
#include "../../content/geometry/Trapezoidalization.h"

int main(){
  using P = Point<long double>;
  using S = SweepLine<long double>::Segment;
  vector<S> s = {{P(0, 0), P(10, 10)}, {P(0, 10), P(10, 0)},
                 {P(0, 20), P(10, 20)}};
  SweepLine<long double> sw(0, 1e-12, s);
  assert(sw.lowerBound(5) == 1);
  sw.setTime(4);
  assert(sw.lowerBound(5) == 1);
  assert(abs(sw.nextEvent() - 5) < 1e-12);
  sw.setTime(6);
  assert(sw.lowerBound(5) == 0);
  sw.setTime(10);
  assert(sw.lowerBound(-100) != -1);
  sw.setTime(10, true);
  assert(sw.lowerBound(-100) == -1);
  rep(it, 0, 100){
    vector<S> a;
    rep(i, 0, 20) a.pb({P(0, rand() % 1000), P(100, rand() % 1000)});
    SweepLine<long double> cur(0, 1e-12, a);
    rep(step, 0, 100){
      long double x = step + 0.314159L;
      cur.setTime(x);
      rep(qi, 0, 20){
        long double q = rand() % 1100 - 50, best = 1e100, bs = 0;
        int id = -1;
        rep(i, 0, sz(a)){
          long double y = a[i].a.y + (a[i].b.y - a[i].a.y)*x/100;
          long double sl = (a[i].b.y - a[i].a.y)/100;
          if(y + 1e-10 < q) continue;
          if(y < best - 1e-10 || (abs(y - best) < 1e-10 &&
              (sl < bs - 1e-10 || (abs(sl - bs) < 1e-10 && i < id))))
            best = y, bs = sl, id = i;
        }
        assert(cur.lowerBound(q) == id);
      }
    }
  }
  cout << "Tests passed!\n";
}
