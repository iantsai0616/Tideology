#include "../utilities/template.h"

#include "../../content/combinatorial/IntPerm.h"

int main(){
  int fact = 1;
  rep(n, 1, 11){
    fact *= n; vi p(n), seen(fact); iota(all(p), 0);
    do {
      int x = permToInt(p);
      assert(0 <= x && x < fact && !seen[x]++);
    }while(next_permutation(all(p)));
  }
  cout << "Tests passed!\n";
}
