#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("no-math-errno,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4")
#pragma GCC target("popcnt,abm,mmx,avx,arch=skylake")
// in main: __builtin_ia32_ldmxcsr(__builtin_ia32_stmxcsr()|0x8040);
#include<unistd.h>
char OB[65536]; int OP;
struct Fl{ ~Fl(){ write(1, OB, OP); } } fl_;
inline int RC() {
  static char buf[65536], *p = buf, *q = buf;
  return p == q && (q = (p = buf) + read(0, buf, 65536)) == buf ? -1 : *p++;
}
inline int R() {
  int c = RC(), s = 1, a = 0;
  while(c != '-' && c < '0' && c != -1) c = RC();
  if(c == '-') s = -1, c = RC();
  for(; c >= '0'; c = RC()) a = a * 10 + (c ^ '0');
  return a * s;
}
inline void W(int n) {
  static char buf[20]; int p = 0;
  if (n < 0) OB[OP++] = '-', n = -n;
  do buf[p++] = '0' + n % 10, n /= 10; while (n);
  while (p) OB[OP++] = buf[--p];
  if (OP > 65500) write(1, OB, OP), OP = 0;
}
