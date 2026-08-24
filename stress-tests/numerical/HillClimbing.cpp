#include "../utilities/template.h"

#include "../../content/numerical/HillClimbing.h"

int main(){
  auto f = [](P p){ return 3*(p[0]-4)*(p[0]-4)+5*(p[1]+2)*(p[1]+2); };
  auto [val, p] = hillClimb(P{100, -70}, f);
  assert(val < 1e-18 && abs(p[0]-4) < 1e-8 && abs(p[1]+2) < 1e-8);
  cout << "Tests passed!\n";
}
