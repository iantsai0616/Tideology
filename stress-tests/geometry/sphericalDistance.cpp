#include "../utilities/template.h"

#include "../../content/geometry/sphericalDistance.h"

int main(){
  const double pi = acos(-1);
  assert(abs(sphericalDistance(0, pi/2, pi/2, pi/2, 3)-3*pi/2) < 1e-9);
  mt19937 rng(123);
  rep(it, 0, 100000){
    double f1 = (double)rng()/rng.max()*2*pi-pi;
    double t1 = (double)rng()/rng.max()*pi;
    double f2 = (double)rng()/rng.max()*2*pi-pi;
    double t2 = (double)rng()/rng.max()*pi;
    double dot = sin(t1)*sin(t2)*cos(f1-f2) + cos(t1)*cos(t2);
    double ans = acos(clamp(dot, -1.0, 1.0));
    assert(abs(sphericalDistance(f1, t1, f2, t2, 1)-ans) < 1e-8);
    assert(isfinite(sphericalDistance(f1, t1, f1+pi, pi-t1, 1)));
  }
  cout << "Tests passed!\n";
}
