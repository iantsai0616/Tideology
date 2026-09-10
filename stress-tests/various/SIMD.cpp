#include "../utilities/template.h"
#include "../../content/various/SIMD.h"

int main(){
#if defined(__x86_64__) || defined(_M_X64)
  alignas(32) int16_t a[16], b[16];
  rep(i, 0, 16) a[i] = i - 8, b[i] = 10 - i;
  ll ans = 0;
  rep(i, 0, 16) if(a[i] < b[i]) ans += a[i]*b[i];
  assert(filteredDotProduct(16, a, b) == ans);
#endif
  cout << "Tests passed!\n";
}
