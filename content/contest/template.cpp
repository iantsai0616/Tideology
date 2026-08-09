#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define all(x) x.begin(),x.end()
#define pb push_back
#define F first
#define S second
#define pii pair<int,int3 >
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define vi vector<int>
#define pb push_back
#ifdef tsao
template <typename T>
ostream& operator << (ostream &o, vector <T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}";
}
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl;
}
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif
void solve(){
	
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t = 1;
	while(t--) solve();
}
