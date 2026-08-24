#include "../utilities/template.h"

#include "../../content/various/BumpAllocator.h"

struct X { long double a; ll b[7]; };

int main(){
  size_t mark = bumpMark();
  void *a = ::operator new(sizeof(X));
  size_t afterA = bumpMark();
  void *b = ::operator new(sizeof(X));
  assert((uintptr_t)a%alignof(max_align_t) == 0);
  assert((uintptr_t)b%alignof(max_align_t) == 0 && a != b);
  size_t used = bumpMark();
  assert(used < mark);
  bumpReset(mark);
  void *c = ::operator new(sizeof(X));
  assert(c == a && bumpMark() == afterA);
  cout << "Tests passed!\n";
}
