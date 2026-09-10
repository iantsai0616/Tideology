#include "../utilities/template.h"

#include "../../content/numerical/Integrate.h"

int main(){
  const double pi = acos(-1);
  assert(abs(quad(-2.0, 3.0, [](double x){ return x*x*x; })-16.25) < 1e-10);
  assert(abs(quad(0.0, pi, [](double x){ return sin(x); })-2) < 1e-10);
  cout << "Tests passed!\n";
}
