/**
 * Source: Cached roots, DIF/DIT convolution
 * Description: NTT/convolution mod 998244353; inputs in $[0, mod)$, size up to $2^{23}$.
 * Time: O(N log N)
 * Status: stress-tested and benchmarked
 * //(2^16)+1, 65537, 3
 * 7*17*(2^23)+1, 998244353, 3
 * 1255*(2^20)+1, 1315962881, 3
 * 51*(2^25)+1, 1711276033, 29
 * only works when sz(A) + sz(B) - 1 <= MAXN
 */
#pragma once
template<int MAXN, ll P, ll RT>
struct NTT {
    ll w[MAXN];
    ll mpow(ll a, ll n) {
        ll re = 1;
        while (n) {
            if (n & 1) re = re * a % P;
            a = a * a % P;
            n >>= 1;
        }
        return re;
    }
    ll minv(ll a) {
        return mpow(a, P - 2);
    }
    NTT() {
        ll dw = mpow(RT, (P - 1) / MAXN);
        w[0] = 1;
        FOR (i, 1, MAXN - 1) w[i] = w[i - 1] * dw % P;
    }
    void bitrev(ll *a, int n) {
        int i = 0;
        for (int j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; (i ^= k) < k; k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
    }
    void operator() (ll *a, int n, bool inv = false) {
        bitrev(a, n);
        for (int L = 2; L <= n; L <<= 1) {
            int dx = MAXN / L, dl = L >> 1;
            for (int i = 0; i < n; i += L) {
                for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
                    ll tmp = a[j + dl] * w[x] % P;
                    if ((a[j + dl] = a[j] - tmp) < 0) a[j + dl] += P;
                    if ((a[j] += tmp) >= P) a[j] -= P;
                }
            }
        }
        if (inv) {
            reverse(a + 1, a + n);
            ll invn = minv(n);
            FOR (i, 0, n - 1) a[i] = a[i] * invn % P;
        }
    }
};
