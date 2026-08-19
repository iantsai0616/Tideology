char IB[1 << 16], OB[1 << 16]; int IP, IL, OP;
inline int RC(){
  if(IP == IL) IP = 0, IL = fread(IB, 1, sizeof IB, stdin);
  return IP == IL ? -1 : IB[IP++];
}
inline int R(){
  int c = RC(), s = 1; unsigned long long x = 0;
  while(c != -1 and c != '-' and (c < '0' or c > '9')) c = RC();
  if(c == '-') s = -1, c = RC();
  while(c >= '0' and c <= '9') x = x * 10 + (c ^ 48), c = RC();
  return s == 1 ? (int)x : (int)(0-x);
}
inline void PC(char c){
  if(OP == (int)sizeof OB) fwrite(OB, 1, OP, stdout), OP = 0;
  OB[OP++] = c;
}
inline void W(int n){
  char s[24]; int p = 0;
  unsigned long long x = n;
  if(n < 0) PC('-'), x = 0 - x;
  do s[p++] = char('0' + x % 10), x /= 10; while(x);
  while(p) PC(s[--p]);
}
struct Flush { ~Flush(){ fwrite(OB, 1, OP, stdout); } } flush;
