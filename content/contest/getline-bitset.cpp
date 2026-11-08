// getline: read a whole line, spaces included
cin >> n; getline(cin >> ws, s); // also skips blank lines
cin.ignore(1e9, '\n'); getline(cin, s); // keep blank lines
if(sz(s) && s.back() == '\r') s.pop_back(); // CRLF input
while(getline(cin, s)){} // every line until EOF
stringstream ss(s); while(ss >> x){} // numbers in a line
while(getline(ss, t, ',')){} // split by ','
// bitset<N>: N is a compile-time constant; ops are O(N/64)
b[i] = 1; b.set(i); b.reset(i); b.flip(i); b.test(i);
b.count(); b.any(); b.none(); b.set(); b.reset();
b.count() == N; // = b.all(), which the all(x) macro breaks
b << k; b >> k; b & c; b | c; b ^ c; ~b; b == c;
for(int i = b._Find_first(); i < N; i = b._Find_next(i)){}
b.to_string(); b.to_ullong(); bitset<N>(string("0101"));
dp |= dp << w; // subset sum: dp[s] = 1 if s is reachable
if(r[i][k]) r[i] |= r[k]; // closure, loop k, i outside
template<int L = 1> void go(int n){ // runtime size
  if(L < n) return go<min(2 * L, MAXN)>(n); bitset<L> b;
}
