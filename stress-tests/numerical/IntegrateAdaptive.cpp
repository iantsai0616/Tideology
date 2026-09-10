#include "../utilities/template.h"

#include "../../content/numerical/IntegrateAdaptive.h"

int main(){
  const double pi = acos(-1);
  assert(abs(quad(0.0, pi, [](double x){ return sin(x); })-2) < 1e-10);
  assert(abs(quad(-3.0, 3.0, [](double x){ return exp(-x*x); })-1.7724146965) < 1e-8);
  cout << "Tests passed!\n";
}
