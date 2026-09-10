#include "../utilities/template.h"

#include "../../content/geometry/linearTransformation.h"

bool eq(P a, P b){ return (a-b).dist() < 1e-9; }

int main(){
  P p0(0, 0), p1(2, 0), q0(5, -2), q1(5, 4);
  assert(eq(linearTransformation(p0, p1, q0, q1, p0), q0));
  assert(eq(linearTransformation(p0, p1, q0, q1, p1), q1));
  assert(eq(linearTransformation(p0, p1, q0, q1, P(1, 1)), P(2, 1)));
  mt19937 rng(123);
  rep(it, 0, 10000){
    p0 = P((int)rng()%100, (int)rng()%100);
    p1 = P((int)rng()%100, (int)rng()%100);
    q0 = P((int)rng()%100, (int)rng()%100);
    q1 = P((int)rng()%100, (int)rng()%100);
    if(p0 == p1) continue;
    assert(eq(linearTransformation(p0, p1, q0, q1, p0), q0));
    assert(eq(linearTransformation(p0, p1, q0, q1, p1), q1));
  }
  cout << "Tests passed!\n";
}
