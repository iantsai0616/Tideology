#include "../utilities/template.h"

#include "../../content/numerical/GoldenSectionSearch.h"

double f(double x){ return (x-3.25)*(x-3.25)+7; }

int main(){
  assert(abs(gss(-1000, 1000, f)-3.25) < 1e-6);
  cout << "Tests passed!\n";
}
